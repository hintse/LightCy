#ifndef PLASMAFRACTAL_H
#define PLASMAFRACTAL_H
#include <vector>
#include "Types.h"

/* type representing the heightmap */
using HeightMap = std::vector<std::vector<float>>;

/* type representing the map of surface normals */
using VectorMap = std::vector<std::vector<Vector>>;

/* class representing a plasma fractal */
class PlasmaFractal 
{
	public:
		/* constructor to construct a fractal of size x by y */
		PlasmaFractal(std::size_t x, std::size_t y);
		
		/* destructor of fractal */
		virtual ~PlasmaFractal() = default;
		
		/* heightmap of the fractal */
		HeightMap heightmap;
		
		/* the surface normals of the surface */
		VectorMap face_normal_map;
		
		/* gets the height (y length, not the max z) of the fractal */
		float get_max_y() const { return heightmap.size(); };
		
		/* gets the width of the fractal */
		float get_max_x() const { return heightmap[0].size(); };
	
	private:
		/* function for generating the random displacement at each
		    each call of the midpoint displacement algorithm */
		virtual float displacement_function(float area) const;
		
		/* the midpoint displacement algorithm */
		void random_midpoint_displacement(std::size_t max_y, std::size_t min_y,
			std::size_t max_x, std::size_t min_x);
			
		/* smooth the fractal so it's more regular */	
		void smooth_fractal(int iter);
		
		/* maximum height of the fractal */
		const float max_height_;
		
		/* maximum start height of the fractal */
		const float max_start_height_;
};

#endif