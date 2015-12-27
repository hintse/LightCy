#ifndef TRAIL_H
#define TRAIL_H
#include "DrawableGameObject.h"
#include "Types.h"
#include "Terrain.h"
#include <vector>

/* class representing the trail left behind by players */
class Trail : public DrawableGameObject
{
	public:
		/* make a trail and set its maximum length, pointer to the
		   terrain the trail is on and the trail's color */
		Trail(int max_length, Terrain* terrain, RGBValue color)
			: max_length_(max_length)
			, terrain_(terrain)
			, color_(color) {};
		
		/* add a point to the trail */
		void add_point(const XYCoordinate& pos);
		
		/* draw the trail */
		virtual void draw();
		
		/* reset the trail */
		virtual void reset();
		
		/* calculates if (a->b) intersects with the trail.  if yes
		   return how much it intersects by (perpendicular distance from
		   b to trail */
		float calculate_intersect_distance(const XYCoordinate& a, 
			const XYCoordinate& b) const; 
			
	private:
		/* trim the trail to make sure its length 
		   doesn't exceed the maximum length */
		void trim();
		
		/* return the length of the trail */
		float length() const;
		
		/* maximum length of the trail */
		int max_length_;
		
		/* terrain the trail is on */
		Terrain* terrain_;
		
		/* points on the trail */
		std::vector<XYCoordinate> trail_;
		
		/* color of the trail */
		RGBValue color_;
};

#endif