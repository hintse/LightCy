#include "LightCy.h"
#include <iostream>
#include <cmath>

static const auto near_z_plane = 0.1f;
static const auto far_z_plane = 10000.0f;
static const auto field_of_view = 90.0f;

static GLuint g_DisplayList = (GLuint)(-1);

LightCy::LightCy(GlutMaster& glutMaster)
	: glutmaster_(&glutMaster)
	, terrain_(map_size_x, map_size_y)
{
	initialise_glut();
	initialise_opengl();
	initialise_game();
}

LightCy::~LightCy()
{
	glutDestroyWindow(windowID);
}

void LightCy::CallBackReshapeFunc(int newWidth, int newHeight)
{
	/* save the window width and height for later use */
	window_width_ = (float)newWidth;
	window_height_ = (float)newHeight;

	/* instruct openGL to use the entirety of our window */
	glViewport(0, 0, newWidth, newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(field_of_view, window_width_ / window_height_, 
				   near_z_plane, far_z_plane);
}

void LightCy::CallBackDisplayFunc(void)
{
	/* our timing information */
	auto fps = 0u;
	/* adjust our timer, which we use for transforming our objects */
	auto dt = timer_.get_previous_frame_delta();
	/* timing information */
	if (timer_.get_fps(fps))
		std::cout << "FPS: " << fps << std::endl;
	
	/* update the start countdown timer and game state */	
	update_start_countdown(dt);
	update_game_state(dt);

	/* clear our colour buffer and depth buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* draw the scene for both players */
	for(auto i = 0; i < cameras_.size(); i++)
	{
		if(i == 0)
			glViewport(0, window_height_/2, window_width_, window_height_/2);
		else
			glViewport(0, 0, window_width_, window_height_/2);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(field_of_view, window_width_ / (window_height_ / 2), near_z_plane, far_z_plane);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glRotatef(cameras_[i].x_angle(), 1.0, 0.0, 0.0);
			glRotatef(cameras_[i].y_angle(), 0.0, 1.0, 0.0);
			glRotatef(cameras_[i].z_angle(), 0.0, 0.0, 1.0);
			glTranslatef(-cameras_[i].x_pos(), -cameras_[i].y_pos(), -cameras_[i].z_pos());
			glCallList(g_DisplayList);
			players_[0].draw();
			players_[1].draw();
			messages_[i].show(window_width_, window_height_);
		glPopMatrix();	
	}
	glutSwapBuffers();
}

void LightCy::CallBackIdleFunc()
{
	/* force another redraw, so we are always drawing as much as possible */
	glutPostRedisplay();
	CallBackDisplayFunc();
}

void LightCy::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	auto keytest = tolower(key);
	
	if (keytest == 'a')
		players_[1].turn_left();
	else if(keytest == 'd')
		players_[1].turn_right();
	else if(keytest == 'q')
		exit(0);
	else if(keytest == 'r')
	{
		if(in_start_menu_)
		{
			for(auto& i : messages_)
				i.clear();
			in_start_menu_ = false;
			start_countdown_ = start_countdown_time;
		}
		else
			reset_game();
	}
}

void LightCy::CallBackSpecialFunc(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT)
		players_[0].turn_left();
	else if(key == GLUT_KEY_RIGHT)
		players_[0].turn_right();
}

void LightCy::initialise_opengl()
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	GLfloat lightAmbient[]={0.5, 0.5, 0.5, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	GLfloat lightDiffuse[] = {0.2, 0.2, 0.2, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	GLfloat lightSpecular[] = { 0.0, 0.0, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	GLfloat lightPosition[] = {map_size_x / 2, map_size_y / 2, 500, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	GLfloat lightModelAmbient[]={0.3,0.3,0.3,1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	GLfloat specref[]={ 1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS, 128);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void LightCy::initialise_glut()
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(window_width_, window_height_);
	glutmaster_->CallGlutCreateWindow("LightCy", this);
	glutmaster_->SetIdleToCurrentWindow();
	glutmaster_->EnableIdleFunction();
}

void LightCy::compile_terrain()
{
	g_DisplayList = glGenLists(1);
	glNewList(g_DisplayList, GL_COMPILE);
	glPushMatrix();
	terrain_.draw();
	glPopMatrix();
	glEndList();
}

void LightCy::initialise_game()
{
	players_.push_back(Player(XYCoordinate(256, 400), RGBValue(1.0, 0, 0), 3, &terrain_));
	players_.push_back(Player(XYCoordinate(256, 100), RGBValue(0, 0.5, 0.9), 1, &terrain_));
	cameras_.push_back(Camera(players_[0]));
	cameras_.push_back(Camera(players_[1]));
	messages_.push_back(Message());
	messages_.push_back(Message());
	compile_terrain();
	messages_[0].write("Press 'R' to begin...", 10);
}

void LightCy::reset_game()
{
	terrain_.reset();
	compile_terrain();
	for(auto& i : players_)
		i.reset();
	for(auto& i : messages_)
		i.clear();
	game_running_ = false;
	start_countdown_ = start_countdown_time;
}

float LightCy::check_lost(const Player& p) const
{
	auto ret = 0.0f;
	for(auto& i : players_)
		ret += p.crash_distance(i.get_trail());
	if(p.x_pos() < 0)
		ret += fabs(p.x_pos());
	else if(p.x_pos() > map_size_x)
		ret += p.x_pos() - map_size_x + 1;
	else if(p.y_pos() < 0)
		ret += fabs(p.y_pos());
	else if(p.y_pos() > map_size_y)
		ret += p.y_pos() - map_size_y + 1;
	return ret;
}

void LightCy::update_start_countdown(float dt)
{
	if(start_countdown_ > 0)
	{
		start_countdown_ -= dt;
		if(start_countdown_ <= 0)
			game_running_ = true;
		for(auto& i : messages_)
		{
			i.clear();
			if(start_countdown_ < 1)
				i.write("Go!", 0.01);
			else
				i.write("Ready?", 0.01);
		}
	}	
}

void LightCy::update_game_state(float dt)
{
	if(game_running_ && dt > 0)
	{
		players_[0].move_forward(dt);
		players_[1].move_forward(dt);
		messages_[0].update(dt);
		messages_[1].update(dt);
		/* check if either player lost */
		auto lose1 = check_lost(players_[0]);
		auto lose2 = check_lost(players_[1]);
		if((lose1 > 0) || (lose2 > 0))
		{
			game_running_ = false;
			if(lose1 == lose2)
			{
				for(auto& i : messages_)
					i.write("It's a draw!", 0);
			}
			else if(lose1 > lose2)
			{
				messages_[0].write("You lost!", 0);
				messages_[1].write("You won!", 0);
			}
			else if(lose2 > lose1)
			{
				messages_[0].write("You won!", 0);
				messages_[1].write("You lost!", 0);
			}
		}
	}
}