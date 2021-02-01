#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	imgSetting();//이미지
	_Pset.img = im.idle;//이미지는 맨처음 idle로

	aniSetting();
	_Pset.ani = an.idle_front;
	_Pset.ani->start();
	Cleft = _run = false;
	Cc = _T = 0;

	_Pset.pt = { WINW / 2, WINH / 2 };

	_Pset.rc = MakeRct(_Pset.pt.x - ((220) / 2), _Pset.pt.y - 192, (220), (224));

	return S_OK;
}

void player::release()
{
	SAFE_DEL(an.idle_front); SAFE_DEL(an.idle_back); SAFE_DEL(an.idle_right);			//노말 _ 보통 애니
	SAFE_DEL(an.walk_front); SAFE_DEL(an.walk_back); SAFE_DEL(an.walk_right);			//노말 / 배틀 _ 걷기 애니
	SAFE_DEL(an.run_front); SAFE_DEL(an.run_back); SAFE_DEL(an.run_right);				//노말 _ 달리기 애니
	SAFE_DEL(an.Bready_front); SAFE_DEL(an.Bready_back); SAFE_DEL(an.Bready_left);		//배틀 _ 준비 애니
	SAFE_DEL(an.SB_front); SAFE_DEL(an.SB_back); SAFE_DEL(an.SB_left);					//배틀 _ 스탠바이 애니
	SAFE_DEL(an.rush_front); SAFE_DEL(an.rush_back); SAFE_DEL(an.rush_right);			//배틀 _ 달려들기 애니
	SAFE_DEL(an.atk_front); SAFE_DEL(an.atk_back); SAFE_DEL(an.atk_right);				//배틀 _ 공격 애니
	SAFE_DEL(an.cri_front); SAFE_DEL(an.cri_back); SAFE_DEL(an.cri_right);				//배틀 _ 크리티컬 애니
	SAFE_DEL(an.spin);												//배틀 _ 스핀 애니
	SAFE_DEL(an.hit_front); SAFE_DEL(an.hit_back); SAFE_DEL(an.hit_right);				//배틀 _ 피격
	SAFE_DEL(an.hit2_front); SAFE_DEL(an.hit2_right);						//배틀 _ 피격2
	SAFE_DEL(an.downs_front); SAFE_DEL(an.downs_back); SAFE_DEL(an.downs_right);		//배틀 _ 쓰러지기 직전
	SAFE_DEL(an.down);												//배틀 _ 쓰러짐
	SAFE_DEL(an.win);												//노말 _ 승리포즈
	SAFE_DEL(an.Bwin_front); SAFE_DEL(an.Bwin_back); SAFE_DEL(an.Bwin_left);			//배틀 _ 승리
	SAFE_DEL(an.cantRun_front); SAFE_DEL(an.cantRun_back); SAFE_DEL(an.cantRun_right);	//노말 _ 못달린다
	SAFE_DEL(an.drink);											//노말 _ 마시기
	SAFE_DEL(an.handsUp_front); SAFE_DEL(an.handsUp_back);					//노말 _ 손들기	
	SAFE_DEL(an.ladder);											//노말 _ 사다리	
	SAFE_DEL(an.tied_front); SAFE_DEL(an.tied_back); SAFE_DEL(an.tied_right);			//노말 _ 묶임	
	SAFE_DEL(an.what_front); SAFE_DEL(an.what_back); SAFE_DEL(an.what_right);			//노말 _ ?
}

void player::update()
{
	keySetting();
	imgSwitch();
	_Pset.rc = MakeRct(_Pset.pt.x - ((220) / 2), _Pset.pt.y - 192, (220), (224));

	if (KEY->down(VK_SPACE))
	{
		if (_Pset.state == NORMAL_IDLE ||
			_Pset.state == NORMAL_WALK ||
			_Pset.state == NORMAL_RUN ||
			_Pset.state == NORMAL_TALK ||
			_Pset.state == NORMAL_EVENT)
		{
			_Pset.state = BATTLE_READY;
		}
		else if (_Pset.state == BATTLE_STANDBY ||
			_Pset.state == BATTLE_ATK ||
			_Pset.state == BATTLE_SKILL ||
			_Pset.state == BATTLE_HIT ||
			_Pset.state == BATTLE_HELP ||
			_Pset.state == BATTLE_WIN)
		{
			_Pset.state = BATTLE_WIN;
		}
	}
	if (KEY->down(VK_LBUTTON) && _Pset.state == BATTLE_STANDBY)
	{
		_Pset.atk = _mouse;
		_Pset.atkS = _Pset.pt;
		_Pset.angle = Angle(static_cast<float>(_Pset.atk.x), static_cast<float>(_Pset.atk.y), static_cast<float>(_Pset.atkS.x), static_cast<float>(_Pset.atkS.y));
		_Pset.Dis = Distance(static_cast<float>(_Pset.atk.x), static_cast<float>(_Pset.atk.y), static_cast<float>(_Pset.atkS.x), static_cast<float>(_Pset.atkS.y));

		if (PI * (1 / 4) < _Pset.angle && _Pset.angle <= PI * (3 / 4)) { _T = 1; }//위쪽보기
		else if (PI * (3 / 4) < _Pset.angle && _Pset.angle <= PI + (PI * (1 / 4))) { _T = 3; }//왼쪽보기
		else if (PI + (PI * (1 / 4)) < _Pset.angle && _Pset.angle <= PI + (PI * (3 / 4))) { _T = 0; }//아래쪽보기
		else { _T = 2; }//오른쪽 보기
		_Pset.state = BATTLE_RUSH;
	}

}

void player::render()
{
	if (KEY->isToggledOn(VK_TAB))
	{
		char str[256], sta[256], stt[256], stT[256];
		sprintf_s(str, "Cc = %d", Cc);
		TextOut(getMemDC(), WINW / 2, WINH / 4, str, static_cast<int>(strlen(str)));
		sprintf_s(sta, "캐릭터 포인트 : %d, %d", _Pset.pt.x, _Pset.pt.y);
		TextOut(getMemDC(), WINW / 2, WINH / 4 + 25, sta, static_cast<int>(strlen(sta)));
		sprintf_s(stt, "각도 = %f", _Pset.angle);
		TextOut(getMemDC(), WINW / 2, WINH / 4 + 50, stt, static_cast<int>(strlen(stt)));
		sprintf_s(stT, "어택 포인트 : %d, %d", _Pset.atk.x, _Pset.atk.y);
		TextOut(getMemDC(), WINW / 2, WINH / 4 - 25, stT, static_cast<int>(strlen(stT)));
		sprintf_s(stT, "시작 포인트 : %d, %d", _Pset.atkS.x, _Pset.atkS.y);
		TextOut(getMemDC(), WINW / 2, WINH / 4 - 50, stT, static_cast<int>(strlen(stT)));

		DrawRct(getMemDC(), _Pset.rc);
		DrawElpC(getMemDC(), _Pset.pt.x, _Pset.pt.y, 32, 32);
		DrawElpC(getMemDC(), _Pset.atk.x, _Pset.atk.y, 32, 32);
		DrawElpC(getMemDC(), _Pset.atkS.x, _Pset.atkS.y, 32, 32);
	}

	if (!Cleft)_Pset.img->animRender(getMemDC(), _Pset.rc.left, _Pset.rc.top, _Pset.ani);
	else if (Cleft)_Pset.img->animRenderH(getMemDC(), _Pset.rc.left, _Pset.rc.top, _Pset.ani);

}

void player::imgSetting()
{
	im.idle = IMG->addF("보통", "res/images/character/chrono/idle.bmp", 660, 672, 3, 3, true, RGB(255, 0, 255));
	im.walk = IMG->addF("걷기", "res/images/character/chrono/walk.bmp", 1320, 672, 6, 3, true, RGB(255, 0, 255));
	im.run = IMG->addF("달리기", "res/images/character/chrono/run.bmp", 1320, 672, 6, 3, true, RGB(255, 0, 255));
	im.Bready = IMG->addF("배틀레디", "res/images/character/chrono/Bready.bmp", 1320, 672, 6, 3, true, RGB(255, 0, 255));
	im.rush = IMG->addF("달려들기", "res/images/character/chrono/rush.bmp", 220, 672, 1, 3, true, RGB(255, 0, 255));
	im.atk = IMG->addF("공격", "res/images/character/chrono/atk.bmp", 1100, 672, 5, 3, true, RGB(255, 0, 255));
	im.Bwin = IMG->addF("배틀승리", "res/images/character/chrono/Bwin.bmp", 660, 896, 3, 4, true, RGB(255, 0, 255));
	im.cantRun = IMG->addF("못달림", "res/images/character/chrono/cantRun.bmp", 660, 672, 3, 3, true, RGB(255, 0, 255));
	im.down = IMG->addF("쓰러짐", "res/images/character/chrono/downs.bmp", 220, 224, 1, 1, true, RGB(255, 0, 255));
	im.downs = IMG->addF("쓰러질때", "res/images/character/chrono/down.bmp", 440, 672, 2, 3, true, RGB(255, 0, 255));
	im.drink = IMG->addF("마심", "res/images/character/chrono/drink.bmp", 440, 224, 2, 1, true, RGB(255, 0, 255));
	im.handsUp = IMG->addF("손들기", "res/images/character/chrono/handsUp.bmp", 220, 448, 1, 2, true, RGB(255, 0, 255));
	im.hit = IMG->addF("피격", "res/images/character/chrono/hit.bmp", 220, 672, 1, 3, true, RGB(255, 0, 255));
	im.hit2 = IMG->addF("피격2", "res/images/character/chrono/hit2.bmp", 220, 448, 1, 2, true, RGB(255, 0, 255));
	im.ladder = IMG->addF("사다리", "res/images/character/chrono/labber.bmp", 880, 224, 4, 1, true, RGB(255, 0, 255));
	im.spin = IMG->addF("회전", "res/images/character/chrono/spin.bmp", 880, 224, 4, 1, true, RGB(255, 0, 255));
	im.tied = IMG->addF("묶임", "res/images/character/chrono/tied.bmp", 440, 672, 2, 3, true, RGB(255, 0, 255));
	im.what = IMG->addF("궁금", "res/images/character/chrono/what.bmp", 220, 672, 1, 3, true, RGB(255, 0, 255));
	im.win = IMG->addF("승리", "res/images/character/chrono/win.bmp", 440, 224, 2, 1, true, RGB(255, 0, 255));
}

void player::aniSetting()
{
	//노말 _ 보통 애니
	{
		an.idle_front = new animation;
		an.idle_front->init(660, 672, 220, 224);
		int Id_F_arr[] = { 0,1,2,1,0 };
		an.idle_front->setPlaylist(Id_F_arr, 5, false);
		an.idle_front->setFPS(1);

		an.idle_back = new animation;
		an.idle_back->init(660, 672, 220, 224);
		int Id_B_arr[] = { 3 };
		an.idle_back->setPlaylist(Id_B_arr, 1, false);
		an.idle_back->setFPS(1);

		an.idle_right = new animation;
		an.idle_right->init(660, 672, 220, 224);
		int Id_R_arr[] = { 6,7,8,7,6 };
		an.idle_right->setPlaylist(Id_R_arr, 5, false);
		an.idle_right->setFPS(1);
	}
	//노말 / 배틀 _ 걷기 애니
	{
		an.walk_front = new animation;
		an.walk_front->init(1320, 672, 220, 224);
		int Wa_F_arr[] = { 0,1,2,3,4,5 };
		an.walk_front->setPlaylist(Wa_F_arr, 6, true);
		an.walk_front->setFPS(1);

		an.walk_back = new animation;
		an.walk_back->init(1320, 672, 220, 224);
		int Wa_B_arr[] = { 6,7,8,9,10,11 };
		an.walk_back->setPlaylist(Wa_B_arr, 6, true);
		an.walk_back->setFPS(1);

		an.walk_right = new animation;
		an.walk_right->init(1320, 672, 220, 224);
		int Wa_R_arr[] = { 12,13,14,15,16,17 };
		an.walk_right->setPlaylist(Wa_R_arr, 6, true);
		an.walk_right->setFPS(1);
	}
	//노말 _ 달리기 애니
	{
		an.run_front = new animation;
		an.run_front->init(1320, 672, 220, 224);
		int Ru_F_arr[] = { 0,1,2,3,4,5 };
		an.run_front->setPlaylist(Ru_F_arr, 6, true);
		an.run_front->setFPS(1);

		an.run_back = new animation;
		an.run_back->init(1320, 672, 220, 224);
		int Ru_B_arr[] = { 6,7,8,9,10,11 };
		an.run_back->setPlaylist(Ru_B_arr, 6, true);
		an.run_back->setFPS(1);

		an.run_right = new animation;
		an.run_right->init(1320, 672, 220, 224);
		int Ru_R_arr[] = { 12,13,14,15,16,17 };
		an.run_right->setPlaylist(Ru_R_arr, 6, true);
		an.run_right->setFPS(1);
	}
	//노말 _ 승리포즈
	{
		an.win = new animation;
		an.win->init(440, 224, 220, 224);
		an.win->setDefPlaylist();
		an.win->setFPS(1);
	}
	//배틀 _ 준비 애니
	{
		an.Bready_front = new animation;
		an.Bready_front->init(1320, 672, 220, 224);
		int Br_F_arr[] = { 0,1,2,3,4,5 };
		an.Bready_front->setPlaylist(Br_F_arr, 6, false);
		an.Bready_front->setFPS(1);

		an.Bready_back = new animation;
		an.Bready_back->init(1320, 672, 220, 224);
		int Br_B_arr[] = { 6,7,8,9,10,11 };
		an.Bready_back->setPlaylist(Br_B_arr, 6, false);
		an.Bready_back->setFPS(1);

		an.Bready_left = new animation;
		an.Bready_left->init(1320, 672, 220, 224);
		int Br_R_arr[] = { 12,13,14,15,16,17 };
		an.Bready_left->setPlaylist(Br_R_arr, 6, false);
		an.Bready_left->setFPS(1);
	}
	//배틀 _ 스탠바이 애니
	{
		an.SB_front = new animation;
		an.SB_front->init(1320, 672, 220, 224);
		int Sb_F_arr[] = { 4,3,4,5 };
		an.SB_front->setPlaylist(Sb_F_arr, 4, true);
		an.SB_front->setFPS(1);

		an.SB_back = new animation;
		an.SB_back->init(1320, 672, 220, 224);
		int Sb_B_arr[] = { 10,9,10,11 };
		an.SB_back->setPlaylist(Sb_B_arr, 4, true);
		an.SB_back->setFPS(1);

		an.SB_left = new animation;
		an.SB_left->init(1320, 672, 220, 224);
		int Sb_L_arr[] = { 16,15,16,17 };
		an.SB_left->setPlaylist(Sb_L_arr, 4, true);
		an.SB_left->setFPS(1);
	}
	//배틀 _ 달려들기 애니
	{
		an.rush_front = new animation;
		an.rush_front->init(220, 672, 220, 224);
		int Rus_F_arr[] = { 0 };
		an.rush_front->setPlaylist(Rus_F_arr, 1, false);
		an.rush_front->setFPS(1);

		an.rush_back = new animation;
		an.rush_back->init(220, 672, 220, 224);
		int Rus_B_arr[] = { 1 };
		an.rush_back->setPlaylist(Rus_B_arr, 1, false);
		an.rush_back->setFPS(1);

		an.rush_right = new animation;
		an.rush_right->init(220, 672, 220, 224);
		int Rus_R_arr[] = { 2 };
		an.rush_right->setPlaylist(Rus_R_arr, 1, false);
		an.rush_right->setFPS(1);
	}
	//배틀 _ 공격 애니
	{
		an.atk_front = new animation;
		an.atk_front->init(1100, 672, 220, 224);
		int At_F_arr[] = { 0,1,2 };
		an.atk_front->setPlaylist(At_F_arr, 3, false);
		an.atk_front->setFPS(1);

		an.atk_back = new animation;
		an.atk_back->init(1100, 672, 220, 224);
		int At_B_arr[] = { 5,6,7 };
		an.atk_back->setPlaylist(At_B_arr, 3, false);
		an.atk_back->setFPS(1);

		an.atk_right = new animation;
		an.atk_right->init(1100, 672, 220, 224);
		int At_R_arr[] = { 10,11,12 };
		an.atk_right->setPlaylist(At_R_arr, 3, false);
		an.atk_right->setFPS(1);
	}
	//배틀 _ 크리티컬 애니
	{
		an.cri_front = new animation;
		an.cri_front->init(1100, 672, 220, 224);
		int Cr_F_arr[] = { 0,1,2,3,4 };
		an.cri_front->setPlaylist(Cr_F_arr, 5, false);
		an.cri_front->setFPS(1);

		an.cri_back = new animation;
		an.cri_back->init(1100, 672, 220, 224);
		int Cr_B_arr[] = { 5,6,7,8,9 };
		an.cri_back->setPlaylist(Cr_B_arr, 5, false);
		an.cri_back->setFPS(1);

		an.cri_right = new animation;
		an.cri_right->init(1100, 672, 220, 224);
		int Cr_R_arr[] = { 10,11,12,13,14 };
		an.cri_right->setPlaylist(Cr_R_arr, 5, false);
		an.cri_right->setFPS(1);
	}
	//배틀 _ 스핀 애니
	{
		an.spin = new animation;
		an.spin->init(880, 224, 220, 224);
		an.spin->setDefPlaylist(false, true);
		an.spin->setFPS(1);
	}
	//배틀 _ 피격
	{
		an.hit_front = new animation;
		an.hit_front->init(220, 672, 220, 224);
		int Hi_F_arr[] = { 0 };
		an.hit_front->setPlaylist(Hi_F_arr, 1, false);
		an.hit_front->setFPS(1);

		an.hit_back = new animation;
		an.hit_back->init(220, 672, 220, 224);
		int Hi_B_arr[] = { 1 };
		an.hit_back->setPlaylist(Hi_B_arr, 1, false);
		an.hit_back->setFPS(1);

		an.hit_right = new animation;
		an.hit_right->init(220, 672, 220, 224);
		int Hi_R_arr[] = { 2 };
		an.hit_right->setPlaylist(Hi_R_arr, 1, false);
		an.hit_right->setFPS(1);
	}
	//배틀 _ 피격2
	{
		an.hit2_front = new animation;
		an.hit2_front->init(220, 448, 220, 224);
		int Hi2_F_arr[] = { 0 };
		an.hit2_front->setPlaylist(Hi2_F_arr, 1, false);
		an.hit2_front->setFPS(1);

		an.hit2_right = new animation;
		an.hit2_right->init(220, 448, 220, 224);
		int Hi2_R_arr[] = { 1 };
		an.hit2_right->setPlaylist(Hi2_R_arr, 1, false);
		an.hit2_right->setFPS(1);
	}
	//배틀 _ 쓰러지기 직전
	{
		an.downs_front = new animation;
		an.downs_front->init(440, 672, 220, 224);
		int Dos_F_arr[] = { 0,1 };
		an.downs_front->setPlaylist(Dos_F_arr, 2, true);
		an.downs_front->setFPS(1);

		an.downs_back = new animation;
		an.downs_back->init(440, 672, 220, 224);
		int Dos_B_arr[] = { 2,3 };
		an.downs_back->setPlaylist(Dos_B_arr, 2, true);
		an.downs_back->setFPS(1);

		an.downs_right = new animation;
		an.downs_right->init(440, 672, 220, 224);
		int Dos_R_arr[] = { 4,5 };
		an.downs_right->setPlaylist(Dos_R_arr, 2, true);
		an.downs_right->setFPS(1);
	}
	//배틀 _ 쓰러짐
	{
		an.down = new animation;
		an.down->init(220, 224, 220, 224);
		an.down->setDefPlaylist();
		an.down->setFPS(1);
	}
	//배틀 _ 승리
	{
		an.Bwin_front = new animation;
		an.Bwin_front->init(660, 896, 220, 224);
		int Bw_F_arr[] = { 0,1,2,9,10 };
		an.Bwin_front->setPlaylist(Bw_F_arr, 5, false);
		an.Bwin_front->setFPS(1);

		an.Bwin_back = new animation;
		an.Bwin_back->init(660, 896, 220, 224);
		int Bw_B_arr[] = { 3,4,5,9,10 };
		an.Bwin_back->setPlaylist(Bw_B_arr, 5, false);
		an.Bwin_back->setFPS(1);

		an.Bwin_left = new animation;
		an.Bwin_left->init(660, 896, 220, 224);
		int Bw_L_arr[] = { 6,7,8,9,10 };
		an.Bwin_left->setPlaylist(Bw_L_arr, 5, false);
		an.Bwin_left->setFPS(1);
	}
	//노말 _ 못달린다
	{
		an.cantRun_front = new animation;
		an.cantRun_front->init(660, 672, 220, 224);
		int Ca_F_arr[] = { 0,1,2,1 };
		an.cantRun_front->setPlaylist(Ca_F_arr, 4, true);
		an.cantRun_front->setFPS(1);

		an.cantRun_back = new animation;
		an.cantRun_back->init(660, 672, 220, 224);
		int Ca_B_arr[] = { 3,4,5,4 };
		an.cantRun_back->setPlaylist(Ca_B_arr, 4, true);
		an.cantRun_back->setFPS(1);

		an.cantRun_right = new animation;
		an.cantRun_right->init(660, 672, 220, 224);
		int Ca_R_arr[] = { 6,7,8,7 };
		an.cantRun_right->setPlaylist(Ca_R_arr, 4, true);
		an.cantRun_right->setFPS(1);
	}
	//노말 _ 마시기
	{
		an.drink = new animation;
		an.drink->init(440, 224, 220, 224);
		int Dr_F_arr[] = { 0,1 };
		an.drink->setPlaylist(Dr_F_arr, 2, true);
		an.drink->setFPS(1);
	}
	//노말 _ 손들기	
	{
		an.handsUp_front = new animation;
		an.handsUp_front->init(220, 448, 220, 224);
		int Ha_F_arr[] = { 0 };
		an.handsUp_front->setPlaylist(Ha_F_arr, 1, false);
		an.handsUp_front->setFPS(1);

		an.handsUp_back = new animation;
		an.handsUp_back->init(220, 448, 220, 224);
		int Ha_B_arr[] = { 1 };
		an.handsUp_back->setPlaylist(Ha_B_arr, 1, false);
		an.handsUp_back->setFPS(1);
	}
	//노말 _ 사다리	
	{
		an.ladder = new animation;
		an.ladder->init(880, 224, 220, 224);
		an.ladder->setDefPlaylist();
		an.ladder->setFPS(1);
	}
	//노말 _ 묶임	
	{
		an.tied_front = new animation;
		an.tied_front->init(440, 672, 220, 224);
		int Ti_F_arr[] = { 0,1 };
		an.tied_front->setPlaylist(Ti_F_arr, 2, true);
		an.tied_front->setFPS(1);

		an.tied_back = new animation;
		an.tied_back->init(440, 672, 220, 224);
		int Ti_B_arr[] = { 2,3 };
		an.tied_back->setPlaylist(Ti_B_arr, 2, true);
		an.tied_back->setFPS(1);

		an.tied_right = new animation;
		an.tied_right->init(440, 672, 220, 224);
		int Ti_R_arr[] = { 4,5 };
		an.tied_right->setPlaylist(Ti_R_arr, 2, true);
		an.tied_right->setFPS(1);
	}
	//노말 _ ?		
	{
		an.what_front = new animation;
		an.what_front->init(220, 672, 220, 224);
		int Wh_F_arr[] = { 0 };
		an.what_front->setPlaylist(Wh_F_arr, 1, false);
		an.what_front->setFPS(1);

		an.what_back = new animation;
		an.what_back->init(220, 672, 220, 224);
		int Wh_B_arr[] = { 1 };
		an.what_back->setPlaylist(Wh_B_arr, 1, false);
		an.what_back->setFPS(1);

		an.what_right = new animation;
		an.what_right->init(220, 672, 220, 224);
		int Wh_R_arr[] = { 2 };
		an.what_right->setPlaylist(Wh_R_arr, 1, false);
		an.what_right->setFPS(1);
	}
}

void player::imgSwitch()
{
	if (_Pset.img != im.idle)
	{
		an.idle_front->stop();
		an.idle_right->stop();
	}
	if (_Pset.img != im.walk)
	{
		an.walk_front->stop();
		an.walk_back->stop();
		an.walk_right->stop();
	}
	if (_Pset.img != im.run)
	{
		an.run_front->stop();
		an.run_back->stop();
		an.run_right->stop();
	}
	if (_Pset.img != im.Bready)
	{
		an.Bready_front->stop();
		an.Bready_back->stop();
		an.Bready_left->stop();
		an.SB_front->stop();
		an.SB_back->stop();
		an.SB_left->stop();
	}
	if (_Pset.img != im.atk)
	{
		an.atk_front->stop();
		an.atk_back->stop();
		an.atk_right->stop();
		an.cri_front->stop();
		an.cri_back->stop();
		an.cri_right->stop();
	}
	if (_Pset.img != im.Bwin)
	{
		an.Bwin_front->stop();
		an.Bwin_back->stop();
		an.Bwin_left->stop();
	}
	switch (_Pset.state)
	{
	case NORMAL_IDLE:
		_Pset.img = im.idle;

		switch (_T)
		{
		case 0:
			_Pset.ani = an.idle_front;
			break;
		case 1:
			_Pset.ani = an.idle_back;
			break;
		case 2:
			if (Cleft)Cleft = false;
			_Pset.ani = an.idle_right;
			break;
		case 3:
			if (!Cleft)Cleft = true;
			_Pset.ani = an.idle_right;
			break;
		}

		_Pset.ani->frameUpdate(TIME->getElapsedTime() * 4);
		if (Cc > 50 && _Pset.ani->isPlay() == FALSE)
		{
			_Pset.ani->start();
			Cc = 0;
		}
		if (_Pset.ani->isPlay() == FALSE && _T != 1)Cc++;
		else if (_Pset.ani->getCurrPlaylistIdx() != 4 && _Pset.ani->getCurrPlaylistIdx() != 0)Cc = 0;

		break;

	case NORMAL_WALK:
		_Pset.img = im.walk;
		if (Cc != 0)Cc = 0;
		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.walk_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.walk_back;
			break;
		case 2:
			if (Cleft)Cleft = false;
			_Pset.ani = an.walk_right;
			break;
		case 3:
			if (!Cleft)Cleft = true;
			_Pset.ani = an.walk_right;
			break;
		}
		_Pset.ani->frameUpdate(TIME->getElapsedTime() * 6);
		_Pset.ani->resume();
		break;

	case NORMAL_RUN:
		_Pset.img = im.run;
		if (Cc != 0)Cc = 0;
		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.run_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.run_back;
			break;
		case 2:
			if (Cleft)Cleft = false;
			_Pset.ani = an.run_right;
			break;
		case 3:
			if (!Cleft)Cleft = true;
			_Pset.ani = an.run_right;
			break;
		}
		_Pset.ani->frameUpdate(TIME->getElapsedTime() * 6);
		_Pset.ani->resume();
		break;

	case BATTLE_READY:
		_Pset.img = im.Bready;
		if (Cc != 0)Cc = 0;
		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.Bready_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.Bready_back;
			break;
		case 2:
			if (!Cleft)Cleft = true;
			_Pset.ani = an.Bready_left;
			break;
		case 3:
			if (Cleft)Cleft = false;
			_Pset.ani = an.Bready_left;
			break;
		}
		_Pset.ani->frameUpdate(TIME->getElapsedTime() * 4);
		if (_Pset.ani->getCurrPlaylistIdx() == 5 && _Pset.ani->isPlay() == FALSE)_Pset.state = BATTLE_STANDBY;
		else if (_Pset.ani->getCurrPlaylistIdx() == 0 && _Pset.ani->isPlay() == FALSE)_Pset.ani->start();
		break;

	case BATTLE_STANDBY:
		_Pset.img = im.Bready;
		if (Cc != 0)Cc = 0;
		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.SB_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.SB_back;
			break;
		case 2:
			if (!Cleft)Cleft = true;
			_Pset.ani = an.SB_left;
			break;
		case 3:
			if (Cleft)Cleft = false;
			_Pset.ani = an.SB_left;
			break;
		}
		_Pset.ani->frameUpdate(TIME->getElapsedTime() * 4);

		if (_Pset.ani->isPlay() == FALSE)_Pset.ani->start();
		break;

	case BATTLE_MOVE:
		_Pset.img = im.walk;
		if (Cc != 0)Cc = 0;
		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.walk_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.walk_back;
			break;
		case 2:
			if (Cleft)Cleft = false;
			_Pset.ani = an.walk_right;
			break;
		case 3:
			if (!Cleft)Cleft = true;
			_Pset.ani = an.walk_right;
			break;
		}
		_Pset.ani->frameUpdate(TIME->getElapsedTime() * 6);
		_Pset.ani->resume();

		break;
	case BATTLE_RUSH:
		_Pset.img = im.rush;

		if (Cc != 0)Cc = 0;
		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.rush_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.rush_back;
			break;
		case 2:
			if (Cleft)Cleft = false;
			_Pset.ani = an.rush_right;
			break;
		case 3:
			if (!Cleft)Cleft = true;
			_Pset.ani = an.rush_right;
			break;
		}
		_Pset.pt.x -= static_cast<int>(cosf(_Pset.angle) * 8);
		_Pset.pt.y -= -static_cast<int>(sinf(_Pset.angle) * 8);
		//스킬과 공격을 결정짓는 인트변수 등을 설정해야 한다
		if (Distance(static_cast<float>(_Pset.pt.x), static_cast<float>(_Pset.pt.y), static_cast<float>(_Pset.atk.x), static_cast<float>(_Pset.atk.y)) <= 50) { _Pset.state = BATTLE_ATK; }

		break;

	case BATTLE_ATK:
		_Pset.img = im.atk;
		if (Cc != 0)Cc = 0;
		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.atk_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.atk_back;
			break;
		case 2:
			if (Cleft)Cleft = false;
			_Pset.ani = an.atk_right;
			break;
		case 3:
			if (!Cleft)Cleft = true;
			_Pset.ani = an.atk_right;
			break;
		}
		_Pset.ani->frameUpdate(TIME->getElapsedTime() * 4);
		if (_Pset.ani->getCurrPlaylistIdx() == 0 && _Pset.ani->isPlay() == FALSE) { _Pset.ani->start(); }
		else if (_Pset.ani->getCurrPlaylistIdx() != 0 && _Pset.ani->isPlay() == FALSE)
		{
			_Pset.ani->stop();
			_Pset.state = BATTLE_RETURN;
		}

		break;

	case BATTLE_RETURN:
		_Pset.img = im.rush;

		if (Cc != 0)Cc = 0;

		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.rush_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.rush_back;
			break;
		case 2:
			if (!Cleft)Cleft = false;
			_Pset.ani = an.rush_right;
			break;
		case 3:
			if (Cleft)Cleft = true;
			_Pset.ani = an.rush_right;
			break;
		}
		_Pset.pt.x += static_cast<int>(cosf(_Pset.angle) * 8);
		_Pset.pt.y += -static_cast<int>(sinf(_Pset.angle) * 8);
		if (50 >= Distance(static_cast<float>(_Pset.pt.x), static_cast<float>(_Pset.pt.y), static_cast<float>(_Pset.atkS.x), static_cast<float>(_Pset.atkS.y))) { _Pset.state = BATTLE_STANDBY; }
		break;
	case BATTLE_WIN:
		_Pset.img = im.Bwin;
		switch (_T)
		{
		case 0:
			if (Cleft)Cleft = false;
			_Pset.ani = an.Bwin_front;
			break;
		case 1:
			if (Cleft)Cleft = false;
			_Pset.ani = an.Bwin_back;
			break;
		case 2:
			if (Cleft)Cleft = true;
			_Pset.ani = an.Bwin_left;
			break;
		case 3:
			if (!Cleft)Cleft = false;
			_Pset.ani = an.Bwin_left;
			break;
		}
		_Pset.ani->frameUpdate(TIME->getElapsedTime() * 4);
		//노말_레디는 전투 후 크로노(1번째 플레이어)쪽으로 모인다, 임시로 idle로 바로 바뀌게 했다
		//if (_Pset.ani->getCurrPlaylistIdx() != 0 && _Pset.ani->isPlay() == FALSE)_Pset.state = NORMAL_READY;
		if (_Pset.ani->getCurrPlaylistIdx() != 0 && _Pset.ani->isPlay() == FALSE)_Pset.state = NORMAL_IDLE;
		else if (_Pset.ani->getCurrPlaylistIdx() == 0 && _Pset.ani->isPlay() == FALSE)_Pset.ani->start();
		break;

	}
}

void player::keySetting()
{
	if (KEY->press(VK_LEFT) && 0 < _Pset.pt.x)
	{
		if (_T != 3)_T = 3;
		if (_run)
		{
			_Pset.state = NORMAL_RUN;
			_Pset.pt.x -= 8;
		}
		if (!_run)
		{
			_Pset.state = NORMAL_WALK;
			_Pset.pt.x -= 5;
		}
	}
	else if (KEY->up(VK_LEFT))
	{
		if (_Pset.state != NORMAL_IDLE)_Pset.state = NORMAL_IDLE;
	}
	if (KEY->press(VK_RIGHT) && WINW > _Pset.pt.x)
	{
		if (_T != 2)_T = 2;
		if (_run)
		{
			_Pset.state = NORMAL_RUN;
			_Pset.pt.x += 8;
		}
		if (!_run)
		{
			_Pset.state = NORMAL_WALK;
			_Pset.pt.x += 5;
		}

	}
	else if (KEY->up(VK_RIGHT))
	{
		if (_Pset.state != NORMAL_IDLE)_Pset.state = NORMAL_IDLE;
	}
	if (KEY->press(VK_UP) && _Pset.pt.y > 0)
	{
		if (_T != 1)_T = 1;
		if (_run)
		{
			_Pset.state = NORMAL_RUN;
			_Pset.pt.y -= 8;
		}
		if (!_run)
		{
			_Pset.pt.y -= 5;
			_Pset.state = NORMAL_WALK;
		}
	}
	else if (KEY->up(VK_UP))
	{
		if (_Pset.state != NORMAL_IDLE)_Pset.state = NORMAL_IDLE;
	}
	if (KEY->press(VK_DOWN) && _Pset.pt.y < WINH)
	{
		if (_T != 0)_T = 0;
		if (_run)
		{
			_Pset.pt.y += 8;
			_Pset.state = NORMAL_RUN;
		}
		if (!_run)
		{
			_Pset.pt.y += 5;
			_Pset.state = NORMAL_WALK;
		}
	}
	else if (KEY->up(VK_DOWN))
	{
		if (_Pset.state != NORMAL_IDLE)_Pset.state = NORMAL_IDLE;
	}
	if (KEY->press('X'))
	{
		if (_run == false)_run = true;
	}
	else if (KEY->up('X')) { if (_run == true)_run = false; }

}
