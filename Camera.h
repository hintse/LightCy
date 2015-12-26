#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"

/* a class representing the camera following a player */
class Camera
{
	public:
		/* constructor for the class */
		Camera(Player& player) : player_(&player){};
		
		/* get the angle of rotation about the x axis */
		float x_angle() const;
		
		/* get the angle of rotation about the y axis */
		float y_angle() const;
		
		/* get the angle of rotation about the x axis */
		float z_angle() const;
		
		/* get the position of the camera along the x axis */
		float x_pos() const;
		
		/* get the position of the camera along the y axis */
		float y_pos() const;
		
		/* get the position of the camera along the z axis */
		float z_pos() const;

	private:
		/* pointer to the player this camera is following */
		Player* player_;
		
		/* constant representing how much the camera should   
		   trail the player by */
		static constexpr auto camera_bike_trail = 15.0f;
		
		/* constant representing how high the camera should
		   be relative to the player */
		static constexpr auto camera_bike_z = 15.0f;

};

#endif