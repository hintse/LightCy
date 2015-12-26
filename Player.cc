#include "Player.h"
#include "glutMaster.h"

const auto bike_length = 1.0;
const auto font_wheel_radius = 1.0;
const auto back_wheel_radius = 0.8;
const auto bike_float = 0.1;
const auto bike_body_radius = 0.2;

Player::Player(XYCoordinate pos, RGBValue color, int direction, Terrain* terrain)
	: pos_(pos)
	, last_pos_(pos)
	, color_(color)
	, direction_(direction)
	, terrain_(terrain)
	, trail_(trail_max_length_, terrain, color)
	, initial_pos_(pos)
	, initial_direction_(direction)
{
	update_tilts();
	trail_.add_point(pos_);
}

void Player::reset()
{
	pos_ = initial_pos_;
	direction_ = initial_direction_;
	trail_.reset();
	update_tilts();
}

void Player::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//set bikes color
	glColor3f(std::get<0>(color_), std::get<1>(color_), std::get<2>(color_)); 
	glPushMatrix();
		//move to bike location
		glTranslatef(std::get<0>(pos_), std::get<1>(pos_), 
			terrain_->get_height(pos_) + font_wheel_radius + bike_float); 
		glPushMatrix();	
			//set direction of bike
			if(y_dir()==1) 
				glRotatef(-90,0.0f,0.0f,1.0f); 
			else if(y_dir()==-1)
				glRotatef(90,0.0f,0.0f,1.0f);
			else if(x_dir()==1)
				glRotatef(180,0.0f,0.0f,1.0f);
			else if(x_dir()==-1)
				glRotatef(0,0.0f,0.0f,1.0f);
			if(y_dir()==0) //bike moving in x direction
				glRotatef(x_angle_,0.0f,1.0f,0.0f); //tilt bike
			else //bike moving in y direction
				glRotatef(y_angle_,0.0f,1.0f,0.0f); //tilt bike
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //rotate so we are drawing parallel to XY plane
			//draw body of bike
			gluCylinder(gluNewQuadric(), bike_body_radius, 
				bike_body_radius, bike_length, 20, 20);  
			//draw front wheel
			gluSphere(gluNewQuadric(), font_wheel_radius, 20, 20); 
			glPushMatrix();
				glTranslatef(0, 0, bike_length);
				gluSphere(gluNewQuadric(), back_wheel_radius, 20, 20); //draw back wheel
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//draw the players trail
	trail_.draw();
}

void Player::update_tilts()
{
	GLfloat head_height;
	GLfloat tail_height;
	head_height = terrain_->get_height(pos_) + bike_float + font_wheel_radius;
	tail_height = terrain_->get_height(std::get<0>(pos_) - bike_length * x_dir(),
		std::get<1>(pos_) + bike_length * y_dir()) + back_wheel_radius + bike_float;
	if((direction_ % 2)==0)
		x_angle_ = atan((head_height-tail_height)/bike_length)*180/3.14;
	else
		y_angle_ = -1.0*atan((head_height-tail_height)/bike_length)*180/3.14;
}

void Player::turn_right()
{
	direction_--;
	if(direction_ == -1)
		direction_ = 3;
	trail_.add_point(pos_);
}
void Player::turn_left()
{
	direction_++;
	if(direction_ == 4)
		direction_ = 0;
	trail_.add_point(pos_);
}

void Player::move_forward(float dt)
{
	last_pos_ = pos_;
	std::get<0>(pos_) += x_dir() * dt * speed_;
	std::get<1>(pos_) += y_dir() * dt * speed_;
	update_tilts();
	trail_.add_point(pos_);
}

float Player::crash_distance(const Trail& t) const
{	
	return t.calculate_intersect_distance(last_pos_, pos_);
}