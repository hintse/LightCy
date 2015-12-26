#include "Terrain.h"
#include "glutMaster.h"

Terrain::Terrain(std::size_t x, std::size_t y)
{
	fractal_ = new PlasmaFractal(x, y);
}

void Terrain::reset()
{
	auto x = fractal_->get_max_x();
	auto y = fractal_->get_max_y();
	delete fractal_;
	fractal_ = new PlasmaFractal(x, y);
}

Terrain::~Terrain()
{
	delete fractal_;
}

void Terrain::draw()
{
	//draw the surface
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for(auto j = 0; j < fractal_->heightmap.size() - 1; j++)
	{
		glBegin(GL_QUAD_STRIP);
		for(auto i = 0; i < fractal_->heightmap[i].size() - 1; i++)
		{
			glColor3f(0.4, 0.4, 0.4);
			glNormal3f(fractal_->face_normal_map[i][j].i(), fractal_->face_normal_map[i][j].j(), 
				fractal_->face_normal_map[i][j].k());
			glVertex3f((float) i,(float) j, fractal_->heightmap[i][j]);	
			
			glNormal3f(fractal_->face_normal_map[i][j + 1].i(), fractal_->face_normal_map[i][j + 1].j(), 
				fractal_->face_normal_map[i][j + 1].k());
			glVertex3f((float) i,(float) j + 1, fractal_->heightmap[i][j + 1]);	
		}
		glEnd();
	}
	//draw the wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(auto j = 0; j < fractal_->heightmap.size() - 1; j++)
	{
		glBegin(GL_QUAD_STRIP);
		for(auto i = 0; i < fractal_->heightmap[i].size() - 1; i++)
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glNormal3f(fractal_->face_normal_map[i][j].i(), fractal_->face_normal_map[i][j].j(), 
				fractal_->face_normal_map[i][j].k());
			glVertex3f((float) i,(float) j, fractal_->heightmap[i][j] + 0.1);	
			
			glNormal3f(fractal_->face_normal_map[i][j + 1].i(), fractal_->face_normal_map[i][j + 1].j(), 
				fractal_->face_normal_map[i][j + 1].k());
			glVertex3f((float) i,(float) j + 1, fractal_->heightmap[i][j + 1] + 0.1);	
		}
		glEnd();
	}
}


float Terrain::get_height(float x, float y) const
{
	auto x1 = int(x);
	auto x2 = int(x1 + 1);
	auto y1 = int(y);
	auto y2 = int(y1 + 1);
	if((x1 < 0) || (y1 < 0))
		return 0;
	if((x2 >= fractal_->get_max_x() - 1) || (y2 >= fractal_->get_max_y() - 1))
		return 0;
	auto h1 = (fractal_->heightmap[x2][y1] - fractal_->heightmap[x1][y1]) * (x - x1) 
		+ fractal_->heightmap[x1][y1]; //interpolate along x
	auto h2 = (fractal_->heightmap[x2][y2] - fractal_->heightmap[x1][y2]) * (x - x1) 
		+ fractal_->heightmap[x1][y2]; //interpolate along x
	return (h2 - h1) * (y - y1) + h1; //interpolate along y
}

float Terrain::get_height(const XYCoordinate& xy) const
{
	return get_height(std::get<0>(xy), std::get<1>(xy));
}