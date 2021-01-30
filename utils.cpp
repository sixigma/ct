#include "stdafx.h"
#include "utils.h"

namespace utils
{
	inline float Distance(float x1, float y1, float x2, float y2)
	{
		return sqrtf(pow(x2 - x1, 2) + pow(y1 - y2, 2));
	}

	inline float Angle(float x1, float y1, float x2, float y2)
	{
		return atan2f(y1 - y2, x2 - x1);
	}

	void Polygon(HDC hDC, vector<POINT> vertices, POINT& pivot, float angle)
	{
		if (vertices.empty()) return;

		if (angle != 0.f)
		{
			float cosA = cosf(angle);
			float sinA = sinf(angle);

			for (POINT& pt : vertices)
			{
				int tempX = static_cast<int>(roundf(cosA * (pt.x - pivot.x) + sinA * (pt.y - pivot.y) + pivot.x));
				pt.y = static_cast<int>(roundf(pivot.y + sinA * (pivot.x - pt.x) + cosA * (pt.y - pivot.y)));
				pt.x = tempX;
			}
		}

		::Polygon(hDC, vertices.data(), static_cast<int>(vertices.size()));
	}
}
