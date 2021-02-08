#include "stdafx.h"
#include "battle.h"
#include "player.h"
#include "enemy.h"
#include "bossGatoStage.h"
#include "crono.h"
#include "lucca.h"

battle::battle()
{
}

battle::~battle()
{
}

HRESULT battle::init()
{


	return S_OK;
}



void battle::release()
{
}

void battle::update()
{
	switch (_battleState)
	{
		case BATTLE_STATE::BATTLE_NOT_START_YET:
		{
			if (_isInBattle)
			{
				_battleState = BATTLE_STATE::BATTLE_POS_RDY;
			}
			break;
		}
		case BATTLE_STATE::BATTLE_POS_RDY:
		{
			POINT& _cronoPos =_crono->getPos();
			POINT& _luccaPos = _lucca->getPos();

			POINT _cronoStartPos = (*_PlBattleStartPos)[0];
			POINT _luccaStartPos = (*_PlBattleStartPos)[1];

			bool _ChkMove = true;

			if (Distance(_cronoPos.x, _cronoPos.y, _cronoStartPos.x, _cronoStartPos.y) > FLT_EPSILON)
			{
				
				_cronoPos.x += (_cronoPos.x > _cronoStartPos.x) ? -min(abs(_cronoPos.x - _cronoStartPos.x), 10) : min(abs(_cronoPos.x - _cronoStartPos.x), 10);
				_cronoPos.y += (_cronoPos.y > _cronoStartPos.y) ? -min(abs(_cronoPos.y - _cronoStartPos.y), 10) : min(abs(_cronoPos.y - _cronoStartPos.y), 10);
				_ChkMove = false;
			}

			else if (Distance(_cronoPos.x, _cronoPos.y, _cronoStartPos.x, _cronoStartPos.y) <= FLT_EPSILON)
			{
				_crono->setT(1);
			}

			if (Distance(_luccaPos.x, _luccaPos.y, _luccaStartPos.x, _luccaStartPos.y) > FLT_EPSILON)
			{
				_luccaPos.x += (_luccaPos.x > _luccaStartPos.x) ? -min(abs(_luccaPos.x - _luccaStartPos.x), 10) : min(abs(_luccaPos.x - _luccaStartPos.x), 10);
				_luccaPos.y += (_luccaPos.y > _luccaStartPos.y) ? -min(abs(_luccaPos.y - _luccaStartPos.y), 10) : min(abs(_luccaPos.y - _luccaStartPos.y), 10);
				_ChkMove = false;
			}

			else if (Distance(_luccaPos.x, _luccaPos.y, _luccaStartPos.x, _luccaStartPos.y) <= FLT_EPSILON)
			{
				_lucca->setT(3);
			}
			
			if (_ChkMove)
			{
				_battleState = BATTLE_STATE::BATTLE_UI_SHOWUP;
			}
			break;
		}
		case BATTLE_STATE::BATTLE_UI_SHOWUP:
		{
			if (_textWindowState == TEXT_WINDOW_STATE::INVISIBLE)
			{
				_battleWindowOpeningCnt++;
				if (_battleWindowOpeningCnt >= 30)
				{
					_crono->setTriggerTime(50);
					_lucca->setTriggerTime(0);

					_plTurnBar[0] = make_shared<progressBar>();
					_plTurnBar[1] = make_shared<progressBar>();

					_plTurnBar[0]->init(387 + 433, 44, 160, 32);
					_plTurnBar[1]->init(387 + 433, 44 + 48, 160, 32);

					_plTurnBar[0]->setGauge(_crono->getTriggerTime(), maxTriggerTime);
					_plTurnBar[1]->setGauge(_lucca->getTriggerTime(), maxTriggerTime);

					_textWindowState = TEXT_WINDOW_STATE::OPENING;
				}
			}

			else if (_textWindowState == TEXT_WINDOW_STATE::OPENING)
			{
				_battleWindowClipCount++;
				if (_battleWindowClipCount == 9)
				{
					_textWindowState = TEXT_WINDOW_STATE::VISIBLE;
					_battleState = BATTLE_STATE::BATTLE_ATK_RDY;
				}

				updateBattleWindow();
			}

			break;
		}
		case BATTLE_STATE::BATTLE_ATK_RDY:
		{
			bool _chkForState = true;

			if (_crono->getState() != BATTLE_STANDBY)
				
			{
				_chkForState = false;
				if (_crono->getState() != BATTLE_READY)
					{
						_crono->setState(BATTLE_READY);
					}
			}

			if (_lucca->getState() != BATTLE_STANDBY)

			{
				_chkForState = false;
					if (_lucca->getState() != BATTLE_READY)
						{
							_lucca->setState(BATTLE_READY);
						}
			}

			if (_chkForState)
			{
				_battleState = BATTLE_STATE::BATTLE_RUNNING;

			}

			updateBattleWindow();
			break;
		}
		case BATTLE_STATE::BATTLE_RUNNING:
		{
			_crono->setTriggerTime(min(_crono->getTriggerTime() + _crono->getSpeed(), maxTriggerTime));
			_lucca->setTriggerTime(min(_lucca->getTriggerTime() + _lucca->getSpeed(), maxTriggerTime));
			(*_enemyVector)[0]->setTriggerTime(min((*_enemyVector)[0]->getTriggerTime() + (*_enemyVector)[0]->getSpeed(), maxTriggerTime));

			if (_crono->getTriggerTime() == maxTriggerTime)
			{
				_shouldPopUpAction[0] = true;
			}

			if (_lucca->getTriggerTime() == maxTriggerTime)
			{
				_shouldPopUpAction[1] = true;
			}

			if ((*_enemyVector)[0]->getTriggerTime() == maxTriggerTime)
			{
				int tempTargetPlayNum;
				tempTargetPlayNum = RNG->getInt(2);
				switch (tempTargetPlayNum)
				{
					case 0:
						if (_crono->getHP() > 0)
						_actionQueue.push([this]()->bool {return (*_enemyVector)[0]->atkSingleTarget(_crono, (*_enemyVector)[0]); });
						(*_enemyVector)[0]->setTriggerTime(0);
						break;
					case 1:
						if (_lucca->getHP() > 0)
						_actionQueue.push([this]()->bool {return (*_enemyVector)[0]->atkSingleTarget(_lucca, (*_enemyVector)[0]); });
						(*_enemyVector)[0]->setTriggerTime(0);
						break;
				}
			}

			//게이지 다 찼을때
			if (_shouldPopUpAction[0] || _shouldPopUpAction[1] || _shouldPopUpAction[2])
			{
				if (KEY->down(VK_DOWN))
				{
					if (arrowPointer < 2)
						arrowPointer++;
				}

				else if (KEY->down(VK_UP))
				{
					if (arrowPointer > 0)
						arrowPointer--;
				}

				// 키 추가 필요
		
			
				else if (KEY->down('V'))
				{
					bool enemyDown = false;
					switch (arrowPointer)
					{
						

						case 0: // 일반 공격
						{
							enemyDown = (*_enemyVector)[0]->hitDamage(999999);
							_shouldPopUpAction[0] = false;
							break;
						}

						case 1: // 스킬
						{

							break;
						}

						case 2: // 아이템
						{

							break;
						}
					}

					if (enemyDown) { _enemyRemainingCnt--; }
				}
			}
			preArrowPointer = arrowPointer; // 어디에 필요한지 확인 필요



			// 게이지 갱신
			_plTurnBar[0]->setGauge(_crono->getTriggerTime(), maxTriggerTime);
			_plTurnBar[1]->setGauge(_lucca->getTriggerTime(), maxTriggerTime);

			if(!_actionQueue.empty())
			{
				if (_actionQueue.front()()) _actionQueue.pop();
			}

			if (_crono->getHP() <= 0)
			{
				_crono->setTriggerTime(0);
				if (_crono->getState() != BATTLE_HELP) _crono->setState(BATTLE_HELP);
			}

			if (_lucca->getHP() <= 0)
			{
				_lucca->setTriggerTime(0);
				if (_lucca->getState() != BATTLE_HELP) _lucca->setState(BATTLE_HELP);
			}

			if ((*_enemyVector)[0]->getEnemyHP() == 0)
			{
				(*_enemyVector)[0]->setTriggerTime(0);
			}

			if (_enemyRemainingCnt == 0)
				_battleState = BATTLE_STATE::BATTLE_ALL_ENEMY_DOWN;

			updateBattleWindow();
			break;
		}
		case BATTLE_STATE::BATTLE_ALL_ENEMY_DOWN:
		{
			_crono->setState(BATTLE_WIN);
			_lucca->setState(BATTLE_WIN);

			_crono->setT(0);
			_lucca->setT(0);

			updateBattleWindow();

			_battleState = BATTLE_STATE::BATTLE_CHECK_REWARD_RDY;
			break;
		}
		case BATTLE_STATE::BATTLE_CHECK_REWARD_RDY:
		{
			if (RNG->getInt(2) == 1)
			{
				_msgQueue.push("Got 1x Tonic!");
			}
		
			_msgQueue.push("Got " + to_string((*_enemyVector)[0]->getEnemyExp()) + " experience point(s)!");
			_msgQueue.push("Got " + to_string((*_enemyVector)[0]->getEnemyTP()) +  " tech point(s)!");
			// 골드 추가 필요
			if (_crono->getState() != BATTLE_HELP)
			{
				_crono->plusExp((*_enemyVector)[0]->getEnemyExp());
			}

			if (_lucca->getState() != BATTLE_HELP)
			{
				_lucca->plusExp((*_enemyVector)[0]->getEnemyExp());
			}
			updateBattleWindow();
			_battleState = BATTLE_STATE::BATTLE_CHECK_REWARD_START;

			break;
		}
		case BATTLE_STATE::BATTLE_CHECK_REWARD_START:
		{
			if (TXT->getTextWindowState2() == TEXT_WINDOW_STATE::INVISIBLE)
			{
				if (!_msgQueue.empty())
				{
					++_msgIntervalCount;
					if (_msgIntervalCount > 10)
					{
						_msgIntervalCount = 0;
						TXT->enqueueBM(_msgQueue.front());
						_msgQueue.pop();
					}
				}
				else
				{
					_battleState = BATTLE_STATE::BATTLE_UI_CLOSE;
					_msgIntervalCount = 0;
				}
			}

			updateBattleWindow();
			break;
		}
		case BATTLE_STATE::BATTLE_UI_CLOSE:
		{

				if (_textWindowState == TEXT_WINDOW_STATE::VISIBLE)
				{
					_textWindowState = TEXT_WINDOW_STATE::CLOSING;
				}
				else if (_textWindowState == TEXT_WINDOW_STATE::CLOSING)
				{
					_battleWindowClipCount--;
					if (_battleWindowClipCount == -1)
					{
						_textWindowState = TEXT_WINDOW_STATE::INVISIBLE;
						_battleWindowClipCount = 0;

						_battleState = BATTLE_STATE::BATTLE_RES_PLAYER;
					}
				}
			updateBattleWindow();
			break;
		}
		case BATTLE_STATE::BATTLE_RES_PLAYER:
		{
			if (_crono->getHP() == 0)
			{
				_crono->hitDamage(-1);
			}

			if (_lucca->getHP() == 0)
			{
				_lucca->hitDamage(-1);
			}

			_crono->setState(NORMAL_IDLE);
			_lucca->setState(NORMAL_IDLE);

			_isChrUnmovable = false;
			_battleState = BATTLE_STATE::BATTLE_END;

			break;
		}
		case BATTLE_STATE::BATTLE_END:
		{
			_isInBattle = false;
			break;	
		}
	}
}

void battle::render()
{
	renderBattleWindow();
}

void battle::updateBattleWindow()
{
	if (_isInBattle)
	{
		if (TXT->getTextWindowPos())
		{
			_yOffset = -606;
		}
		else
		{
			_yOffset = 0;
		}

		_shouldRenderUsingWindowCoords = TRUE;

		IMG->render("전투 적 목록 창 스킨", hTempDC, 0, 0);
		IMG->render("전투 스탯 창 스킨", hTempDC, 387, 0);
		TXT->render(hTempDC, "Gato", 64, 44);			//적 1의 이름 출력
		//TXT->render(hTempDC, "GreenImp", 64, 92);		//적 2의 이름 출력
		//TXT->render(hTempDC, "Roly", 64, 140);		//적 3의 이름 출력
		TXT->render(hTempDC, _playChrNames[0], 416, 45); // 플레이어 1의 캐릭터 이름 출력
		//TXT->render(hTempDC, _playChrNames[2], 416, 686+44); // 플레이어 2의 캐릭터 이름 출력

		IMG->frameRender("흰색 타일셋0", hTempDC, 612, 11, 8, 3); //hp 글자 출력
		IMG->frameRender("흰색 타일셋0", hTempDC, 641, 11, 10, 3); //hp 글자 출력
		IMG->frameRender("흰색 타일셋0", hTempDC, 737, 11, 9, 3); //mp 글자 출력
		IMG->frameRender("흰색 타일셋0", hTempDC, 769, 11, 10, 3); //mp 글자 출력

		//HP10이하 일때 HP,:,MP 12프레임으로 깜빡거림 (타일셋 교체로 표현하기)
		//플레이어 1의 전투 액션 창, HP,MP,턴바

		int currentHP;
		currentHP = _crono->getHP();
		string str1 = to_string(currentHP);
		string tempstr;

		if (currentHP == 0)
		{
			_crono->setState(BATTLE_HELP);
			tempstr = "비활성 타일셋0";
			_blinkCount[0] = 24;
		}
		else if (currentHP <= 10)
		{
			if (_blinkCount[0] < 12)
			{
				tempstr = "비활성 타일셋0";
			}
			else tempstr = "흰색 타일셋0";
			_blinkCount[0]--;
			if (_blinkCount[0] == 0)
				_blinkCount[0] = 24;
		}
		else tempstr = "흰색 타일셋0";

		for (int i = 0; i < str1.size(); i++)
		{
			if (currentHP < 10)
			{
				int frameX = str1[i] - '0';
				IMG->frameRender(tempstr, hTempDC, 676 + i * 32, 45, frameX, 4);
			}
			else if (currentHP < 100)
			{
				int frameX = str1[i] - '0';
				IMG->frameRender(tempstr, hTempDC, 644 + i * 32, 45, frameX, 4);
			}

			else if (currentHP > 100)
			{
				int frameX = str1[i] - '0';
				IMG->frameRender(tempstr, hTempDC, 612 + i * 32, 45, frameX, 4);
			}
		}

		IMG->frameRender(tempstr, hTempDC, 710, 45, 11, 3); //hp와 mp사이의 :(콜론)

		int currentMP;
		currentMP = _crono->getMP();
		string str2 = to_string(currentMP);

		for (int i = 0; i < str2.size(); i++)
		{
			if (currentMP < 10)
			{
				int frameX = str2[i] - '0';
				IMG->frameRender(tempstr, hTempDC, 776 + i * 32, 45, frameX, 4);
			}

			else if (currentMP < 100)
			{
				int frameX = str2[i] - '0';
				IMG->frameRender(tempstr, hTempDC, 744 + i * 32, 45, frameX, 4);
			}
		}

		if (_shouldPopUpAction[0])
		{
			IMG->render("전투 창 스킨", hTempDC, 0, 0);
			TXT->render(hTempDC, "Att.", 64, 44);
			TXT->render(hTempDC, "Tech", 64, 92);
			TXT->render(hTempDC, "Item", 64, 140);

			IMG->frameRender("위치 표시 타일셋", hTempDC, 0, 19 + arrowPointer * 48, 0, 1);

		}

		_plTurnBar[0]->render(hTempDC);


		_shouldRenderUsingWindowCoords = FALSE;

	}
}

void battle::renderBattleWindow()
{
	if(_textWindowState == TEXT_WINDOW_STATE::OPENING || _textWindowState == TEXT_WINDOW_STATE::CLOSING)
		IMG->renderZ(5000, IMG->find("전투 윈도우 용 빈 비트맵"), getMemDC(), 0 + _currOrg.x , 641 + _yOffset + _currOrg.y + 12 * (8 - _battleWindowClipCount), 0, 12 * (8 - _battleWindowClipCount), WINW, 24 * _battleWindowClipCount);
	else if (_textWindowState == TEXT_WINDOW_STATE::VISIBLE)
		IMG->renderZ(5000, IMG->find("전투 윈도우 용 빈 비트맵"), getMemDC(), 0 + _currOrg.x, 641 + _yOffset + _currOrg.y, 0, 0, WINW, 192);
}

void battle::init(vector<enemy*>* _enemyVector, vector<gameNode*>* _playerVector, vector<POINT>* _PlBattleStartPos, vector<POINT>* _EmBattleStartPos)
{

	arrowPointer = 0;
	preArrowPointer = 0;

	_blinkCount[0] = 24;
	_blinkCount[1] = 24;
	_blinkCount[2] = 24;

	_yOffset = 0;

	hTempDC = IMG->find("전투 윈도우 용 빈 비트맵")->getMemDC();

	this->_playerVector = _playerVector;
	this->_enemyVector = _enemyVector;
	this->_PlBattleStartPos = _PlBattleStartPos;
	this->_EmBattleStartPos = _EmBattleStartPos;



	_battleState = BATTLE_STATE::BATTLE_NOT_START_YET;

	_textWindowState = TEXT_WINDOW_STATE::INVISIBLE;

	_msgIntervalCount = 0;
	_battleWindowOpeningCnt = _battleWindowClipCount = 0;
	_enemyRemainingCnt = this->_enemyVector->size();

	_crono = reinterpret_cast <crono*> ((*_playerVector)[0]);
	_lucca = reinterpret_cast <lucca*> ((*_playerVector)[1]);

	 _shouldPopUpAction[0] = false;
	 _shouldPopUpAction[1] = false;
	 _shouldPopUpAction[2] = false;
}
