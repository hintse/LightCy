#include "PlasmaFractal.h"
#include <cstdlib>
#include <cmath>


const int number_of_smooths = 20;
const int smooth_factor = 1000;

PlasmaFractal::PlasmaFractal(std::size_t x, std::size_t y)
	: heightmap(x, std::vector<float>(y, -1))
	, face_normal_map(x, std::vector<Vector>())
	, max_height_((x > y ? x : y) * 0.2)
	, max_start_height_(max_height_ * 0.2)
{
	//build the fractal
	heightmap[0][0] = fmodf(rand(), max_start_height_);
	heightmap[0][y - 1] = fmodf(rand(), max_start_height_);
	heightmap[x - 1][0] = fmodf(rand(), max_start_height_);
	heightmap[x - 1][y - 1] = fmodf(rand(), max_start_height_);
	random_midpoint_displacement(y - 1, 0, x - 1, 0);
	smooth_fractal(number_of_smooths);
	
	//build the face normal map
	for(auto i = 0; i < x - 1; i++)
	{
		face_normal_map.push_back(std::vector<Vector>());
		for(auto j = 0; j < y - 1; j++)
		{
			auto a = Vertex(i, j, heightmap[i][j]);
			auto b = Vertex(i + 1, j, heightmap[i + 1][j]);
			auto c = Vertex(i, j + 1, heightmap[i][j + 1]);
			face_normal_map[i].push_back(cross_product(Vector(a, b), Vector(a, c)));
			face_normal_map[i][j] /= face_normal_map[i][j].magnitude();
		}
	}
	
}

void PlasmaFractal::smooth_fractal(int iter)
{
	if(iter == 0)
		return;
	auto average_height = 0.0f;
	for(auto i = 0; i < heightmap.size() - 1; i++)
	{
		for(auto j = 0; j < heightmap[0].size() - 1; j++)
		{
			average_height=(heightmap[i][j]+heightmap[i+1][j]+heightmap[i][j+1]+heightmap[i+1][j+1])/4;
			heightmap[i][j]=((heightmap[i][j]-average_height)/smooth_factor)+average_height;
			heightmap[i+1][j]=((heightmap[i+1][j]-average_height)/smooth_factor)+average_height;
			heightmap[i][j+1]=((heightmap[i][j+1]-average_height)/smooth_factor)+average_height;
			heightmap[i+1][j+1]=((heightmap[i+1][j+1]-average_height)/smooth_factor)+average_height;
		}
	}
	smooth_fractal(iter - 1);
}

void PlasmaFractal::random_midpoint_displacement(std::size_t max_y, std::size_t min_y,
	std::size_t max_x, std::size_t min_x)
{
	auto mid_y = min_y + (max_y - min_y) / 2;
	auto mid_x = min_x + (max_x - min_x) / 2;
	auto area = (max_x - min_x) * (max_y - min_y);
	
	if(area > 1)
	{
		//top
		heightmap[mid_x][max_y] = (heightmap[max_x][max_y] + heightmap[min_x][max_y]) / 2;
		//bottom
		heightmap[mid_x][min_y] = (heightmap[max_x][min_y] + heightmap[min_x][min_y]) / 2;
		//left
		heightmap[min_x][mid_y] = (heightmap[min_x][max_y] + heightmap[min_x][min_y]) / 2;
		//right
		heightmap[max_x][mid_y] = (heightmap[max_x][max_y] + heightmap[max_x][min_y]) / 2;
		//middle
		heightmap[mid_x][mid_y] = (heightmap[min_x][max_y] + heightmap[min_x][min_y]
							+ heightmap[max_x][max_y] + heightmap[max_x][min_y]) / 4;
		//randomly displace the midpoint
		heightmap[mid_x][mid_y] += displacement_function(area);
		//check that we didn't exceed the maximum height and that we don't have negative height
		if(heightmap[mid_x][mid_y] < 0)
			heightmap[mid_x][mid_y] = -heightmap[mid_x][mid_y];
		if(heightmap[mid_x][mid_y] > max_height_)
			heightmap[mid_x][mid_y] = max_height_;
		//recursively call this function on the smaller squares
		random_midpoint_displacement(mid_y, min_y, mid_x, min_x);
		random_midpoint_displacement(max_y, mid_y, mid_x, min_x);
		random_midpoint_displacement(mid_y, min_y, max_x, mid_x);
		random_midpoint_displacement(max_y, mid_y, max_x, mid_x);
	}
	else
	{
		heightmap[mid_x][mid_y] = (heightmap[min_x][max_y] + heightmap[min_x][min_y]
			+ heightmap[max_x][max_y] + heightmap[max_x][min_y]) / 4;
	}
}

float PlasmaFractal::displacement_function(float area) const
{
	return 0.5 * sqrt(area) * ((((float) rand() / RAND_MAX)) - 0.5); 
}
