#ifndef CONST_UTILS_H
#define CONST_UTILS_H

#include "cocos2d.h"

#include <string>
#include <sstream>
#include <stdlib.h>
#include <cmath>

using namespace std;
using namespace cocos2d;

class Utils
{
	public:
		static string intToString(int i);
		static float randomf(float min, float max);
		static int random(int min, int max);
		static float coord(float pCoordinate);
		static float distance(float dX0, float dY0, float dX1, float dY1);
		static bool probably(int pProbably);
		static CCPoint vectorNormalize(float pVectorX, float pVectorY, float pMultipleFactor);

		static float Pi;
};

#endif