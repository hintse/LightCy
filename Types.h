#ifndef TYPES_H
#define TYPES_H
#include <tuple>
#include <cmath>

/* type representing RGB values */
using RGBValue = std::tuple<float, float, float>;

/* type for XY coordinates */
using XYCoordinate = std::tuple<float, float>;

/* type for XYZ coordinates */
using XYZCoordinate = std::tuple<float, float, float>;

/* check to see if c is between a and b */
inline bool between(float a, float b, float c);

/* check to see if c is on the left of vector a -> b */
inline bool left(const XYCoordinate& a, const XYCoordinate& b, const XYCoordinate& c);

/* check to see if a, b and c are collinear and if c is between a, b */
inline bool on_line_between_points(const XYCoordinate& a, 
	const XYCoordinate& b, const XYCoordinate& c);

/* checks to see if a->b intersects with c->d */
inline bool intersects(const XYCoordinate& a, 
	const XYCoordinate& b, const XYCoordinate& c, const XYCoordinate& d);
	
/* calculate the perpendicular distance from c to line a -> b */
inline float perpendicular_distance(const XYCoordinate& a, 
	const XYCoordinate& b, const XYCoordinate& c);

/* class representing a vertex */
class Vertex
{
	public:
		/* make a vertex with x y z coordinates */
		Vertex(float x, float y, float z)
			: x_(x)
			, y_(y)
			, z_(z) {};
		
		/* make a vertex with x y coordinates, z will be 0 */
		Vertex(XYCoordinate xy)
			: x_(std::get<0>(xy))
			, y_(std::get<1>(xy))
			, z_(0) {};
		
		/* make a vertex with x y z coordinates */
		Vertex(const XYZCoordinate& xyz)
			: x_(std::get<0>(xyz))
			, y_(std::get<1>(xyz))
			, z_(std::get<2>(xyz)) {};
		
		/* gets the x coordinate of the vertex */
		float x() const { return x_; };
		
		/* gets the y coordinate of the vertex */
		float y() const { return y_; };
		
		/* gets the z coordinate of the vertex */
		float z() const { return z_; };
		
	private:
		/* x, y, z coordinates of the vertex */
		float x_, y_, z_;
};

/* class representing a vector */
class Vector 
{
	public:
		/* make a vector going from "from" to "to" */
		Vector(Vertex from, Vertex to) 
			: i_(to.x() - from.x())
			, j_(to.y() - from.y())
			, k_(to.z() - from.z()) {};
		
		/* make a vector by specifying its components directly */
		Vector(float i, float j, float k)
			: i_(i)
			, j_(j)
			, k_(k) {};
		
		/* take cross products */
		Vector cross_product(const Vector& other) 
		{
			this->i_ = this->j_ * other.k() - this->k_ * other.j();
			this->j_ = this->i_ * other.k() - this->k() * other.i();
			this->k_ = this->i_ * other.j() - this->j() * other.i();
			return *this;
		};
		
		/* divide each component by a number */
		Vector operator/=(float x) { i_ /= x; j_ /= x; k_ /= x; return *this; };
		
		/* magnitude of the vector */
		float magnitude() const { return sqrt(i_ * i_ + j_ * j_ + k_ * k_); };
		
		/* get the i component of the vector */
		float i() const { return i_; };
		
		/* get the i component of the vector */
		float j() const { return j_; };
		
		/* get the i component of the vector */
		float k() const { return k_; };
	private:
		/* i, j, k components of the vertex */
		float i_, j_, k_;
};

/* binary version of cross product */
inline Vector cross_product(Vector lhs, const Vector& rhs) 
{
	return lhs.cross_product(rhs);
}

/* begin definition of declared functions */
inline bool between(float a, float b, float c)
{
	return (((a<c)&&(b>c))||((a>c)&&(b<c)));
}

inline bool left(const XYCoordinate& a, const XYCoordinate& b, const XYCoordinate& c)
{
	return (std::get<0>(b) - std::get<0>(a)) * 
		(std::get<1>(c) - std::get<1>(a)) - 
		(std::get<0>(c) - std::get<0>(a)) *
		(std::get<1>(b) - std::get<1>(a)) >=0;
}

inline bool on_line_between_points(const XYCoordinate& a, const XYCoordinate& b, 
	const XYCoordinate& c)
{
	if(std::get<0>(a) == std::get<0>(b))
	{
		if(std::get<0>(c) == std::get<0>(a)) //collinear
			return between(std::get<1>(a), std::get<1>(b), std::get<1>(c));
		else
			return false;
	}
	if(std::get<1>(a) == std::get<1>(b))
	{
		if(std::get<1>(c) == std::get<1>(a)) //collinear
			return between(std::get<0>(a), std::get<0>(b), std::get<0>(c));
		else
			return false;
	}
	return false;
}

inline bool intersects(const XYCoordinate& a, const XYCoordinate& b, 
	const XYCoordinate& c, const XYCoordinate& d)
{
	if((a == b) || (c == d) || (a == c) || (a == d) || (b == c) || (b == d))
		return false;
	else if(on_line_between_points(a, b, c) || on_line_between_points(a, b, d))
		return true;
	else if(on_line_between_points(c, d, a) || on_line_between_points(c, d, b))
		return true;
	return (!left(a, b, c)  ^ !left(a, b, d)) && (!left(c, d, a) ^ !left(c, d, b));	
}

inline float perpendicular_distance(const XYCoordinate& a, const XYCoordinate& b, 
	const XYCoordinate& c)
{
	if(std::get<0>(a) == std::get<0>(b))
	{
		return fabs(std::get<0>(c) - std::get<0>(a));
	}
	else if(std::get<1>(a) == std::get<1>(b))
	{
		return fabs(std::get<1>(c) - std::get<1>(a));
	}
	return -1;
}

#endif
