#include "GameMgr.h"
#include "ObjectMgr.h"
#include "Func.h"
#include "Draw.h"

GameMgr& mgr = GameMgr::get();

GameMgr& GameMgr::get(){
	static GameMgr inst;
	return inst;
}

void GameMgr::update(){
	Input::update();//キー更新
	Sound::update();

	sceneMgr.update();

}


void GameMgr::draw(){
	sceneMgr.draw();
}

void GameMgr::draw2(){
}

void GameMgr::init(){

}

void GameMgr::loadResource(){
	GraphAE::get().load();
	GraphButton::get().load();
	GraphB::get().load();
	GraphHue::get().load();
	Graph::get().load();
	GraphDiv::get().load();
	Font::get().load();
	Sound::get().load();
}

void GameMgr::loadButton(){
}


GameMgr::GameMgr() :
sceneMgr(std::make_unique<MainScene>())
{
};


