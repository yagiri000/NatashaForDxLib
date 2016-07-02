#pragma once

#include <deque>
#include <memory>
#include <sstream>
#include <cassert>
#include <crtdbg.h>

#include "myglobal.h"


//�V�[�����N���X
//������p�����Ďg��
class IScene
{
protected:
	int eFrame;
public:
	IScene();
	virtual void update();
	int getEFrame();
	void setEFrame(int x);
	virtual void draw() = 0;
};


//�V�[���Ǘ��N���X
//stack + unique_ptr�ŊǗ�
class SceneMgr
{
public:
	std::deque<std::unique_ptr<IScene>> sceneList;
	std::unique_ptr<IScene> next;
	std::unique_ptr<IScene> nextAllPop;
	bool isPopFront;

	SceneMgr();
	SceneMgr(std::unique_ptr<IScene> p);

	void add(std::unique_ptr<IScene> new_object);
	void shiftPopBack(std::unique_ptr<IScene> new_object);
	void shiftPopAll(std::unique_ptr<IScene> new_object);
	void popBack();
	void update();
	void draw();

private:
	void pop();
};


class PreTitleScene : public IScene{
public:
	PreTitleScene();
	virtual void update();
	virtual	void draw();
};


class TitleScene : public IScene{
public:
	TitleScene();
	virtual void update();
	virtual	void draw();
};


class MainScene : public IScene{
public:
	MainScene();
	virtual void update();
	virtual void draw();
};


class ResultScene : public IScene{
public:
	ResultScene();
	virtual void update();
	virtual void draw();
};
