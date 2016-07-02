//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once
#include <iostream>

#include "Effects.h"
#include "Button.h"

#include "Abstract.h"
#include "Screen.h"
#include "Easing.h"
#include "Scene.h"

class GameMgr{
public:
	GameMgr(const GameMgr& r) = delete;//�R�s�[�֎~
	GameMgr& operator=(const GameMgr& r) = delete;//����֎~
	static GameMgr& get();

	SceneMgr sceneMgr;
	
	void update();
	void draw();
	void draw2();

	void init();
	void loadResource();
	void loadButton();

private:
	GameMgr();
};


extern GameMgr& mgr;