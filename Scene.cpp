#include "Scene.h"
#include "Func.h"
#include "GameMgr.h"
#include "ObjectMgr.h"
#include "MyString.h"


IScene::IScene():
eFrame(0)
{
}

void IScene::update(){ 
	eFrame++; 
}

int IScene::getEFrame(){ 
	return eFrame; 
}

void IScene::setEFrame(int x){
	eFrame = x; 
}


SceneMgr::SceneMgr() : 
isPopFront(false)
{
}

SceneMgr::SceneMgr(std::unique_ptr<IScene> p) : 
isPopFront(false)
{
	add(std::move(p));
}

//スタックにシーンオブジェクトを追加
void SceneMgr::add(std::unique_ptr< IScene > new_object)
{
	sceneList.emplace_back(std::move(new_object));
}

//一番上のシーンを破棄し、新たなシーンを入れる
void SceneMgr::shiftPopBack(std::unique_ptr< IScene > new_object){
	next = std::move(new_object);
}

//一番上のシーンを破棄し、新たなシーンを入れる
void SceneMgr::shiftPopAll(std::unique_ptr< IScene > new_object){
	nextAllPop = std::move(new_object);
}

//一番上のシーンを破棄
void SceneMgr::popBack(){
	isPopFront = true;
}

//一番上のシーンを破棄
void SceneMgr::pop(){
	sceneList.pop_back();
}

void SceneMgr::update(){
	assert(!sceneList.empty() && "update() called when scene stack empty");
	
	sceneList.back()->update();

	if (isPopFront){
		sceneList.pop_back();
		isPopFront = false;
	}

	//shift関数が呼ばれnextAllPopに何か入っていれば、すべてのシーンを破棄して次のシーンに入れ替える
	if (nextAllPop != nullptr){
		sceneList.clear();
		sceneList.emplace_back(std::move(nextAllPop));
	}

	//shift関数が呼ばれnextに何か入っていれば、現在のシーンを破棄して次のシーンに入れ替える
	if (next != nullptr){
		sceneList.pop_back();
		sceneList.emplace_back(std::move(next));
	}
}

void SceneMgr::draw(){
	assert(!sceneList.empty() && "update() called when scene stack empty");
	sceneList.back()->draw();

	if(1){
		int num = 0;
		for (auto &i : sceneList){
			String str = String() + typeid(*i).name() + "(" + i->getEFrame() / 60 + ")";
			Draw.textBox(Vector2(20, 20 + 32 * num), 0xFFFFFF, font("SegoeUI18"), str(), 255, HorizontalPlace::left, VerticalPlace::top, Vector2(8, 8), 0x000000, 200);
			num++;
		}
	}
}





PreTitleScene::PreTitleScene(){
}

void PreTitleScene::update(){
	eFrame++;
	//PreTitleSceneはダミーのシーンなので、いきなり次のシーンに飛ぶ
	mgr.sceneMgr.shiftPopBack(std::make_unique<TitleScene>());
}

void PreTitleScene::draw(){
}




TitleScene::TitleScene()
{
}

void TitleScene::update(){
	eFrame++;
}

void TitleScene::draw(){
}




MainScene::MainScene(){
	mgr.init();
}

void MainScene::update(){
	eFrame++;

	obj.effect_.update();
	obj.button_.update();

}

void MainScene::draw(){
	Draw.normal(Vector2::zero, Graph::handle("back"), 255);
	obj.effect_.draw();
	obj.button_.draw();
}



ResultScene::ResultScene()
{
}

void ResultScene::update(){
	eFrame++;
}


void ResultScene::draw(){
}
