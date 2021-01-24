#pragma once

constexpr float PI = 3.1415927f; // pi
constexpr float PI2 = 6.283185f; // 2 pi

namespace utils
{
	float Distance(float x1, float y1, float x2, float y2);
	float Angle(float x1, float y1, float x2, float y2);
}

inline void DrawLine(HDC hDC, int x1, int y1, int x2, int y2)
{
	MoveToEx(hDC, (_shouldRenderUsingWindowCoords ? x1 : (x1 - _currOrg.x)), (_shouldRenderUsingWindowCoords ? y1 : (y1 - _currOrg.y)), nullptr);
	LineTo(hDC, (_shouldRenderUsingWindowCoords ? x2 : (x2 - _currOrg.x)), (_shouldRenderUsingWindowCoords ? y2 : (y2 - _currOrg.y)));
}

inline POINT MakePt(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline RECT MakeRct(int x, int y, int width, int height)
{
	RECT rct = { x, y, x + width, y + height };

	return rct;
}

inline RECT MakeRctC(int x, int y, int width, int height)
{
	RECT rct = { x - (width / 2) , y - (height / 2), x + (width / 2), y + (height / 2) };
	return rct;
}

inline void DrawRct(HDC hDC, int x, int y, int width, int height)
{
	Rectangle(hDC, (_shouldRenderUsingWindowCoords ? x : (x - _currOrg.x)),
			  (_shouldRenderUsingWindowCoords ? y : (y - _currOrg.y)),
			  (_shouldRenderUsingWindowCoords ? x : (x - _currOrg.x)) + width,
			  (_shouldRenderUsingWindowCoords ? y : (y - _currOrg.y)) + height);
}

inline void DrawRctC(HDC hDC, int x, int y, int width, int height)
{
	Rectangle(hDC, (_shouldRenderUsingWindowCoords ? x : (x - _currOrg.x)) - (width / 2),
			  (_shouldRenderUsingWindowCoords ? y : (y - _currOrg.y)) - (height / 2),
			  (_shouldRenderUsingWindowCoords ? x : (x - _currOrg.x)) + (width / 2),
			  (_shouldRenderUsingWindowCoords ? y : (y - _currOrg.y)) + (height / 2));
}

inline void DrawRct(HDC hDC, RECT& rct)
{
	Rectangle(hDC, (_shouldRenderUsingWindowCoords ? rct.left : (rct.left - _currOrg.x)),
			  (_shouldRenderUsingWindowCoords ? rct.top : (rct.top - _currOrg.y)),
			  (_shouldRenderUsingWindowCoords ? rct.right : (rct.right - _currOrg.x)),
			  (_shouldRenderUsingWindowCoords ? rct.bottom : (rct.bottom - _currOrg.y)));
}

inline void DrawElp(HDC hDC, int x, int y, int width, int height)
{
	Ellipse(hDC, (_shouldRenderUsingWindowCoords ? x : (x - _currOrg.x)),
			(_shouldRenderUsingWindowCoords ? y : (y - _currOrg.y)),
			(_shouldRenderUsingWindowCoords ? x : (x - _currOrg.x)) + width,
			(_shouldRenderUsingWindowCoords ? y : (y - _currOrg.y)) + height);
}

inline void DrawElpC(HDC hDC, int x, int y, int width, int height)
{
	Ellipse(hDC, (_shouldRenderUsingWindowCoords ? x : (x - _currOrg.x)) - (width / 2),
			(_shouldRenderUsingWindowCoords ? y : (y - _currOrg.y)) - (height / 2),
			  (_shouldRenderUsingWindowCoords ? x : (x - _currOrg.x)) + (width / 2),
			  (_shouldRenderUsingWindowCoords ? y : (y - _currOrg.y)) + (height / 2));
}

inline void DrawElp(HDC hDC, RECT& rct)
{
	Ellipse(hDC, (_shouldRenderUsingWindowCoords ? rct.left : (rct.left - _currOrg.x)),
			  (_shouldRenderUsingWindowCoords ? rct.top : (rct.top - _currOrg.y)),
			  (_shouldRenderUsingWindowCoords ? rct.right : (rct.right - _currOrg.x)),
			  (_shouldRenderUsingWindowCoords ? rct.bottom : (rct.bottom - _currOrg.y)));
}