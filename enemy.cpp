#include "stdafx.h"
#include "enemy.h"
#include "crono.h"
#include "lucca.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}

bool enemy::attack(float Distance)
{
	/*
	// 원거리 공격 / 근거리 공격 / 원거리에서 접근하여 근거리 공격 타입 나누기
	if (_State == NORMAL_IDLE)
	{
		if (Distance < 30)
		{
			_State = BATTLE_ATK;
			//각 플레이어에 넣어진 bool "캐릭이름" hit 함수로 피격자의 피격상태 표현

			//공격시 방향 확인용 조건
		}

		else // 공격 사정거리가 아닐 시 움직임을 매개변수로 받을 수는 없는지
		{
			if (_State != BATTLE_HIT)
			{
				POINT& _cronoPos = _crono->getPos();
				POINT& _luccaPos = _lucca->getPos();
				_ChaSet.pt.x += (_ChaSet.pt.x > _cronoPos.x) ? -min(abs(_cronoPos.x - _ChaSet.pt.x), 10) : min(abs(_cronoPos.x - _ChaSet.pt.x), 10);
				_ChaSet.pt.y += (_ChaSet.pt.y > _cronoPos.y) ? -min(abs(_cronoPos.y - _ChaSet.pt.y), 10) : min(abs(_cronoPos.y - _ChaSet.pt.y), 10);
			}
		}
	}
	*/
	return true;
}
