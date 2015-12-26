#include "Camera.h"

float Camera::x_pos() const
{
	return player_->x_pos() - player_->x_dir() * camera_bike_trail;
}

float Camera::y_pos() const
{
	return player_->y_pos() - player_->y_dir() * camera_bike_trail;
}

float Camera::z_pos() const
{
	return player_->z_pos() + camera_bike_z;
}

float Camera::x_angle() const
{
	if(player_->x_dir() == 0)
		return -45.0f - player_->y_angle();
	else
		return -45.0f - player_->x_angle();
}

float Camera::y_angle() const
{
	return 0.0f;
}

float Camera::z_angle() const
{
	if(player_->y_dir() == 1)
		return 0.0f;
	else if(player_->y_dir() == -1)
		return 180.0f;
	else if(player_->x_dir() == 1)
		return 90.0f;
	else if(player_->x_dir() == -1)
		return -90.0f;
	return 0;
}