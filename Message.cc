#include "Message.h"
#include "glutMaster.h"

void Message::show(float width, float height) const
{
	if(message_ == "")
		return;
	glColor3f(1.0,1.0,1.0); //color of the text
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, width, height, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			auto x = width / 2 - message_.length() * 4; //try to center the text
			auto y = height / 2;
			glRasterPos3f(x, y, 1.0f);
			for(auto c : message_)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);              
			}
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void Message::update(float dt)
{
	if(timeout_ == 0)
		return;
	timeout_ -= dt;
	if(timeout_ <= 0)
	{
		message_ = "";
		timeout_ = 0;
	}
}

void Message::write(std::string message, float timeout)
{
	
	message_ = message;
	timeout_ = timeout;
}

void Message::clear()
{
	message_ = "";
	timeout_ = 0;
}