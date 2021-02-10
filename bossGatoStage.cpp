#include "stdafx.h"
#include "bossGatoStage.h"
#include "player.h"
#include "battle.h"

HRESULT bossGatoStage::init()
{
	//_mapImg = imageManager::getSingleton()->add("bossGato", L"res/images/maps/bossGato.bmp");

	load2("res/mapInfo/가토/saveMap1.map");
	currPlPos = &pl->getCrono()->getPos();

	if (getPrevMapNum() == 1) *currPlPos = { 644, 850 };
	else if (getPrevMapNum() == 2) *currPlPos = { 660, 780 };
	else if (getPrevMapNum() == 4) *currPlPos = { 1050, 1000 }; 
	setMapNum(3);

	// ========================================================

	tileMapLoad("보스맵", 1024, 1024);


	exit.push_back({ 542, 962, 542 + 194, 962 + 56 });
	prevPlPos = *currPlPos;

	_battle = make_shared<battle>();


	//_battle->setLinkTo(pl);
	_yOffset = 0;

	_gato = make_shared<gato>();
	_gato->init();

	_PlBattleStartPos.push_back({ 520, 620 });
	_PlBattleStartPos.push_back({ 604, 492 });

	_EmBattleStartPos.push_back({ WINW / 2 + 40 , WINH / 2 + 78 });

	_playerVector.push_back(pl->getCrono());
	_playerVector.push_back(pl->getLucca());

	_enemyVector.push_back(_gato.get());

	_battle->init(&_enemyVector, &_playerVector, &_PlBattleStartPos, &_EmBattleStartPos);

	_dialogueStateNum = 0;

	return S_OK;
}

void bossGatoStage::update()
{
	
	//if (currPlPos->y - probeY > 1024) gameScene::goToMap(2);
	zorderUpdate();
	if (PtInRect(&exit[0], *currPlPos))
	{
		gameScene::goToMap(2);
		return;
	}

	mapCollision();
	

	_gato->update();

	POINT tempGatoPos = _gato->getPt();

	switch (_dialogueStateNum)
	{
		case 0:
		{
			if (KEY->down('V') && Distance(currPlPos->x, currPlPos->y, tempGatoPos.x, tempGatoPos.y) < 100) //&& Angle 각도 조건 추가 필요)
			{
				_isChrUnmovable = true;
				pl->getCrono()->setState(NORMAL_IDLE);
				pl->getLucca()->setState(NORMAL_IDLE);
				// if (가토가 원래 위치로 노래 자세를 취하면)
				{
					TXT->enqueueL
					(
						"T<w-2>hey <w1>call me [1]<w-2>Gat<w1>o[0]{\n"
						"<w-2>I h<w1>a<w-2>ve me<w1>tal <w-2>jo<w1>i<w-2>nt<w1><w-2>s{<w1>\n"
						"<w-2>Be<w1>a<w-2>t m<w1><w-2>e u<w1><w-2>p{<w1>\n"
						"And <w-2>ea<w1>rn [3]<w-2>15 <w1>Silv<w-2>er <w1><w-2>Po<w1><w-2>int<w1>s[0]{"
					);
				}
				++_dialogueStateNum;
			}
			break;
		}
		case 1:
		{
			if (TXT->getTextWindowState1() == TEXT_WINDOW_STATE::INVISIBLE)
				_isInBattle = true;
			if (_battle->getBattleState() == BATTLE_STATE::END) // 전투가 종료되었으면
			{
				++_dialogueStateNum;
			}
			break;
		}
		case 2:
		{
			// 리마인더: 가토가 원래 위치로 돌아가게 하는 코드를 작성할 자리

			// if (가토가 원래 위치로 돌아와서 노래 자세를 취하면)
			{
				if (!_battle->getResult())
				{
					TXT->enqueueL
					(
						"I lo<w1>s<w-2>t{ Yo<w1><w-2>u won{<w1>\n"
						"<w-2>He<w1><w-2>re'<w1><w-2>s [3]15 P<w1>o<w-2>in<w1><w-2>ts[0]{\n"
						"Now w<w1>a<w-2>sn<w1><w-2>'t <w1><w-2>that [4]f<w1>u<w-2>n[0]!<w1>?{"
					);
				}
				++_dialogueStateNum;
			}
			break;
		}
		case 3:
		{
			if (TXT->getTextWindowState1() == TEXT_WINDOW_STATE::INVISIBLE)
			{
				++_dialogueStateNum;
				_isChrUnmovable = false;
			}
			break;
		}
	}

	if (_isInBattle)
	{
		_battle->update();
	}
	prevPlPos = *currPlPos;
}

void bossGatoStage::release()
{

	cO.clear();
	eR.clear();

	//_tile.clear();


	exit.clear();

	_PlBattleStartPos.clear();
	_EmBattleStartPos.clear();
	_playerVector.clear();
	_enemyVector.clear();

	_battle.reset();
	_gato->release();
	_gato.reset();
	_dialogueStateNum = 0;
	_isInBattle = false;

}

void bossGatoStage::render()
{

	//IMG->render("bossGato", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);
	//IMG->render("보스맵", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);
	IMG->renderZ(zGrid, IMG->find("보스맵Z"), getMemDC(), 0, 0);
	IMG->renderZ(0, IMG->find("보스맵"), getMemDC(), 0, 0);

	//IMG->render("bossGato", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);
	_gato->render();
	_shouldRenderUsingWindowCoords = TRUE;
	_battle->render();
	_shouldRenderUsingWindowCoords = FALSE;
#ifdef _DEBUG
		{
			if (KEY->isToggledOn(VK_CAPITAL))
			{
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
				HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
				HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
				HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
				for (size_t i = 0; i < cO.size(); ++i)
				{
					DrawRct(getMemDC(), cO[i]);
				}
				DeleteObject(SelectObject(getMemDC(), hOPen));
				DeleteObject(SelectObject(getMemDC(), hOBrush));
				}
			if (KEY->isToggledOn(VK_CAPITAL))
			{
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
				HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
				HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
				HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
				for (size_t i = 0; i < eR.size(); ++i)
				{
					DrawRct(getMemDC(), eR[i]);
				}
				DeleteObject(SelectObject(getMemDC(), hOPen));
				DeleteObject(SelectObject(getMemDC(), hOBrush));
			}
			if (KEY->isToggledOn(VK_CAPITAL))
			{
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
				HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
				HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
				HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
				for (size_t i = 0; i < exit.size(); ++i)
				{
					DrawRct(getMemDC(), exit[i]);
				}
				DeleteObject(SelectObject(getMemDC(), hOPen));
				DeleteObject(SelectObject(getMemDC(), hOBrush));
			}
		}

#endif
	}