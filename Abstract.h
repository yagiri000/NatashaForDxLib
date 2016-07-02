//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once

//#include <DxLib.h>
#include <vector>
#include <algorithm>
#include <memory>


class IObject
{
public:
	bool IsDead;

	IObject();
	virtual void init();
	virtual void update() = 0;
	virtual void draw() = 0;
};


class IMgr{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
};


template <class T>
class Mgr : public IMgr
{
public:
	std::vector<std::shared_ptr<T>> v;
	std::vector<std::shared_ptr<T>> addv;
	std::shared_ptr<T> now;
	Mgr(){}

	void add(std::shared_ptr<T> p){
		addv.emplace_back(p);
	}

	void clearVec(){
		v.clear();
		addv.clear();
	}

	//�e�v�f�X�V�E����
	void update(){
		for (auto &i = v.begin(); i < v.end(); i++){
			now = *i;
			(**i).update();
		}
		//IsDead��true�Ȃ珜��
		auto rmv = std::remove_if(v.begin(), v.end(),
			[](std::shared_ptr<T> p)->bool{
			return p->IsDead;
		}
		);
		v.erase(rmv, v.end());

		//�ǉ�
		for (auto &i = addv.begin(); i < addv.end(); i++){
			//(**i).update();
			v.emplace_back(*i);
		}
		addv.clear();
	}

	//�`��
	void draw(){
		for (auto& i : v){
			i->draw();
		}
		//�f�o�b�O�p�E���݂̗v�f����\��
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);	DrawFormatString(20, 60, 0xFFFFFF, "NUM : %d", v.size()) ;
	}
};


/*
template <class T>
class MgrNotCpy : public IMgr
{
public:

	std::vector<std::shared_ptr<T>> v;
	std::shared_ptr<T> now;
	MgrNotCpy(){}

	void add(std::shared_ptr<T> p){
		v.emplace_back(p);
	}


	//�e�v�f�X�V�E����
	void update(){
		for (auto &i = v.begin(); i < v.end(); i++){
			now = *i;
			(**i).update();
		}
		//IsDead��true�Ȃ珜��
		auto rmv = std::remove_if(v.begin(), v.end(),
			[](std::shared_ptr<T> p)->bool{
			return p->IsDead;
		}
		);
		v.erase(rmv, v.end());

	}

	//�`��
	void draw(){
		for (auto& i : v){
			i->draw();
		}
		//�f�o�b�O�p�E���݂̗v�f����\��
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);	DrawFormatString(20, 60, 0xFFFFFF, "NUM : %d", v.size()) ;
	}
};
*/

