#include "stdafx.h"
#include "mapManager.h"
#include "player.h"

HRESULT mapManager::init()
{
	return S_OK;
}

void mapManager::release()
{
	
}

void mapManager::update()
{
	
}

void mapManager::render()
{

}

void mapManager::mapCollision()
{
	for (size_t i = 0; i < cO.size(); ++i)
	{
		if (currPlPos->x - probeX < cO[i].right && currPlPos->x + probeX > cO[i].left
			&& currPlPos->y - probeY < cO[i].bottom && currPlPos->y + probeY > cO[i].top
			
			)
		{
			int Xdiff = prevPlPos.x - currPlPos->x; //전 x 위치와 현 x 위치의 차이
			int Ydiff = prevPlPos.y - currPlPos->y; //전 y 위치와 현 y 위치의 차이

			if (Xdiff > 0) currPlPos->x = cO[i].right + probeX;
			else if (Xdiff < 0) currPlPos->x = cO[i].left - probeX;
			if (Ydiff > 0)currPlPos->y = cO[i].bottom + probeY;
			else if (Ydiff < 0)currPlPos->y = cO[i].top - probeY;
		}
	}
	prevPlPos = *currPlPos;
}


