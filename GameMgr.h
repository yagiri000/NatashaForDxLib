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
	GameMgr(const GameMgr& r) = delete;//ÉRÉsÅ[ã÷é~
	GameMgr& operator=(const GameMgr& r) = delete;//ë„ì¸ã÷é~
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