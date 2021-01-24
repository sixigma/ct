#include "stdafx.h"
#include "utils.h"

namespace utils
{
	float Distance(float x1, float y1, float x2, float y2)
	{
		float deltaX = x2 - x1;
		float deltaY = y1 - y2;
		return sqrtf(deltaX * deltaX + deltaY * deltaY);
	}

	float Angle(float x1, float y1, float x2, float y2)
	{
		float deltaX = x2 - x1;
		float deltaY = y1 - y2;
		float angle = atan2f(deltaY, deltaX);
		return angle;
	}
}