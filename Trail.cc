#include "Trail.h"
#include <cmath>
#include "glutMaster.h"

const float trail_thickness = 0.2;
const float trail_below_ground = 3;
const float trail_height = 2;

void Trail::add_point(const XYCoordinate& pos)
{
	trail_.push_back(pos);
	trim();
}

float Trail::length() const
{
	auto last_node = trail_.begin();
	auto length = 0.0f;
	for(auto i = trail_.begin() + 1; i != trail_.end(); ++i)
	{
		length += Vector(*last_node, *i).magnitude();
		last_node = i;
	}
	return length;
}

void Trail::trim()
{
	if(length() > max_length_)
	{
		trail_.erase(trail_.begin());
		trim();
	}
}

void Trail::draw()
{
	if(trail_.size() < 2)
		return;
	//set color, notice the alpha
	glColor4f(std::get<0>(color_), std::get<1>(color_), std::get<2>(color_),0.8f); 
	auto last_height = 0.0f;
	auto last_node = trail_.begin();
	auto current_height = terrain_->get_height(std::get<0>(*last_node), std::get<1>(*last_node));
	for(auto i = trail_.begin() + 1; i != trail_.end(); ++i)
	{
		last_height = current_height;
		current_height = terrain_->get_height(std::get<0>(*i), std::get<1>(*i));
		glBegin(GL_QUAD_STRIP);
		if(std::get<0>(*last_node) == std::get<0>(*i))
		{
			glVertex3f(std::get<0>(*last_node) + trail_thickness, std::get<1>(*last_node),
				last_height - trail_below_ground); //v0
			glVertex3f(std::get<0>(*last_node) + trail_thickness, std::get<1>(*i),
				current_height - trail_below_ground); //v1
			glVertex3f(std::get<0>(*last_node) + trail_thickness, std::get<1>(*last_node),
				last_height + trail_height); //v2
			glVertex3f(std::get<0>(*last_node) + trail_thickness, std::get<1>(*i),
				current_height + trail_height); //v3
			glVertex3f(std::get<0>(*last_node) - trail_thickness, std::get<1>(*last_node),
				last_height + trail_height); //v4
			glVertex3f(std::get<0>(*last_node) - trail_thickness, std::get<1>(*i),
				current_height + trail_height); //v5
			glVertex3f(std::get<0>(*last_node) - trail_thickness, std::get<1>(*last_node),
				last_height - trail_below_ground); //v6
			glVertex3f(std::get<0>(*last_node) - trail_thickness, std::get<1>(*i),
				current_height - trail_below_ground); //v7		
		}
		else
		{
			glVertex3f(std::get<0>(*last_node), std::get<1>(*last_node) + trail_thickness,
				last_height - trail_below_ground); //v0
			glVertex3f(std::get<0>(*i), std::get<1>(*last_node) + trail_thickness,
				current_height - trail_below_ground); //v1
			glVertex3f(std::get<0>(*last_node), std::get<1>(*last_node) + trail_thickness,
				last_height + trail_height); //v2
			glVertex3f(std::get<0>(*i), std::get<1>(*last_node) + trail_thickness,
				current_height + trail_height); //v3
			glVertex3f(std::get<0>(*last_node), std::get<1>(*last_node) - trail_thickness,
				last_height + trail_height); //v4
			glVertex3f(std::get<0>(*i), std::get<1>(*last_node) - trail_thickness,
				current_height + trail_height); //v5
			glVertex3f(std::get<0>(*last_node), std::get<1>(*last_node) - trail_thickness,
				last_height - trail_below_ground); //v6
			glVertex3f(std::get<0>(*i), std::get<1>(*last_node) - trail_thickness,
				current_height - trail_below_ground); //v7		
		}
		glEnd();
		last_node = i;
	}	
}

void Trail::reset()
{
	while(trail_.size() != 0)
		trail_.pop_back();
}

float Trail::calculate_intersect_distance(const XYCoordinate& a, 
	const XYCoordinate& b) const
{
	auto last_node = trail_.begin();
	for(auto i = trail_.begin() + 1; i != trail_.end(); ++i)
	{
		if(intersects(a, b, *i, *last_node))
			return perpendicular_distance(*i, *last_node, b) + 0.1; 
			//0.1 is for head on collision where perpendicular distance is 0.
		last_node = i;
	}
	return 0.0f;
}
