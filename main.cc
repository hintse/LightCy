#include "glutMaster.h"
#include "glutWindow.h"
#include "LightCy.h"
#include <iostream>
#include <ctime>

int main()
{
	srand(time(NULL));
	GlutMaster glutMaster;
	LightCy lightCy(glutMaster);
	glutMaster.CallGlutMainLoop();

}