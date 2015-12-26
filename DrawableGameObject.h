#ifndef DRAWABLEGAMEOBJECT_H
#define DRAWABLEGAMEOBJECT_H

/* abstract class representing any object in the  
   game that is drawable */
class DrawableGameObject {
	public:
		/* draw the object */
		virtual void draw() = 0;
		
		/* reset the object to its initial state */
		virtual void reset() = 0;
};

#endif