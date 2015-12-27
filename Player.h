#ifndef PLAYER_H
#define PLAYER_H

#include "DrawableGameObject.h"
#include "Types.h"
#include "Terrain.h"
#include "Trail.h"

/* class representing a player */
class Player : public DrawableGameObject
{
	public:
		/* construct the player starting at pos, drawn with color, initially facing
		   direction.  also need the terrain to store a handle to */
		Player(XYCoordinate pos, RGBValue color, int direction, Terrain* terrain);
		
		/* draw the player */
		virtual void draw();
		
		/* reset the player */
		virtual void reset();
		
		/* move the player forward */
		void move_forward(float dt);
		
		/* make the player turn left */
		void turn_left();
		
		/* make the player turn right */
		void turn_right();
		
		/* gets the position of player in the x axis */
		const float x_pos() const { return std::get<0>(pos_); };
		
		/* gets the position of player in the y axis */
		const float y_pos() const { return std::get<1>(pos_); };
		
		/* gets the position of player in the z axis */
		const float z_pos() const { return terrain_->get_height(pos_); };
		
		/* gets the rotation of the player about the x axis */
		const float x_angle() const { return x_angle_; };
		
		/* gets the rotation of the player about the x axis */
		const float y_angle() const { return y_angle_; };
		
		/* returns the i component of a unit vector representing
		   the direction of the player */
		const int x_dir() const { return direction_ == 0 ? 1 : (direction_ == 2 ? -1 : 0); };
		
		/* returns the j component of a unit vector representing
		   the direction of the player */		
		const int y_dir() const { return direction_ == 1 ? 1 : (direction_ == 3 ? -1 : 0); };
		
		/* returns the position of the player */
		const XYCoordinate pos() const { return pos_; };
		
		/* returns the last position of the player */
		const XYCoordinate last_pos() const { return last_pos_; }
		
		/* returns a reference to the trail of the player */
		const Trail& get_trail() const { return trail_; };
		
		/* returns a value greater than 0 if the player has crashed into
		   the trail specified.  if greater than 0, it represents how much
		   the player has crashed */
		float crash_distance(const Trail& t) const;
		
	private:
		/* updates the x_angle_ and y_angle_ of the player.
		   these angles are due to tilting on the terrain */
		void update_tilts();
		
		/* position of the player */
		XYCoordinate pos_;
		
		/* last position of the player */
		XYCoordinate last_pos_;
		
		/* what color the player is */
		RGBValue color_;
		
		/* direction the player is facing.  0 is east
		   1 is north, 2 is west, 3 is south */
		int direction_;
		
		/* rotation of the player about the x axis */
		float x_angle_;
		
		/* rotation of the player about the y axis */
		float y_angle_;
		
		/* pointer to the terrain the player is on */
		Terrain* terrain_;
		
		/* speed of the player */
		float speed_ = 30;
		
		/* maximum trail length of the player */
		int trail_max_length_ = 250;
		
		/* trail the player leaves behind */
		Trail trail_;
		
		/* initial position of the player (so we can reset it) */
		XYCoordinate initial_pos_;
		
		/* initial direction of the player (so we can reset it) */
		int initial_direction_;
		
};

#endif