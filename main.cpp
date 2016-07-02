#pragma once

#include <DxLib.h>
#include <iostream>

#include "myglobal.h"
#include "Resource.h"
#include "Func.h"
#include "Draw.h"
#include "GameMgr.h"
#include "Screen.h"
#include "Effects.h"

#include "Color.h"
#include "Dir.h"

#include "MyString.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowIconID(101);
	SetMainWindowText("Natasha");
	ChangeWindowMode(TRUE);
	SetGraphMode(ScreenWidth, ScreenHeight, 32);
	Func::setBackgroundColor0x(0x000000);
	SetOutApplicationLogValidFlag(FALSE);//logを生成しないように設定
	if (DxLib_Init() == 1){ return -1; }//初期化に失敗時にエラーを吐かせて終了

	Input::get();
	Screen::get();
	GameMgr::get().loadResource();
	GameMgr::get().loadButton();

	while( ProcessMessage() == 0)
	{
		GameMgr::get().update();

		ButtonAdder::addDValBoolButton("ToWhite");
		if (DVal::bool_["ToWhite"]){
			Screen::setWhiteOut(5);
			Screen::setShake(10);
			DVal::bool_["ToWhite"] = false;
		}

		if (Input::keyDown(KEY_INPUT_Z)){
			Screen::setWhiteOut(5);
			Screen::setShake(10);
		}

		if (Input::keyDown(KEY_INPUT_X)){
		}

		if (Input::keyDown(KEY_INPUT_C)){
		}

		Screen::DrawStart(); //描画開始, ClearScreen
		{
			GameMgr::get().draw();
			Draw.center(Input::mousePos(), Graph::handle("dot32"), 255);
		}
		Screen::DrawEnd(); //描画終了, ScreenFlip

		//フラグがtrueならゲーム終了
		if (gameEndFlag){
			break;
		}
	}


	DxLib_End();
	return 0;
}

