#ifndef TERRAIN_H
#define TERRAIN_H
#include "PlasmaFractal.h"
#include "DrawableGameObject.h"
#include "Types.h"

/* class representing the terrain */
class Terrain : public DrawableGameObject
{
	public:
		/* construct a x by y terrain */
		Terrain(std::size_t x, std::size_t y);
		
		/* destructor */
		~Terrain();
		
		/* draw the terrain */
		virtual void draw();
		
		/* make a new terrain */
		virtual void reset();
		
		/* get the height of the terrain at (x, y) */
		float get_height(float x, float y) const;
		
		/* get the height of the terrain at xy */
		float get_height(const XYCoordinate& xy) const;
		
	private:
		/* pointer to the fractal this terrain uses */
		PlasmaFractal* fractal_;
};
#endif