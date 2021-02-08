#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	_crono = new crono;
	_crono->init();
	_lucca = new lucca;
	_lucca->init();
	_frog = new frog;
	_frog->init();

	return S_OK;
}

void player::release()
{
	_crono->release();
	SAFE_DEL(_crono);
	_lucca->release();
	SAFE_DEL(_lucca);
	_frog->release();
	SAFE_DEL(_frog);
}

void player::update()
{
	_crono->update();
	_lucca->update();
	_frog->update();
	if (KEY->down('0'))
	{
		if (_cha == 0)_cha = 1;
		else if (_cha == 1)_cha = 2;
		else if (_cha == 2)_cha = 0;
	}
	if (_cha == 0)_crono->keySetting();
	else if (_cha == 1)_lucca->keySetting();
	else if (_cha == 2)_frog->keySetting();

	if (_crono->atkCheck()) { _frog->setState(BATTLE_HIT); }
	else if (_frog->getState() == BATTLE_HIT && !_crono->atkCheck()) { _frog->setState(NORMAL_IDLE); }

}

void player::render()
{
	
	_crono->render();
	_lucca->render();
	_frog->render();
}

