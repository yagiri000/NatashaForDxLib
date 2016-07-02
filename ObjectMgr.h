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

//�e�I�u�W�F�N�g���X�}�[�g�|�C���^�̌`�ŏ������Ă��邾���̃N���X�i�V���O���g���j
class ObjectMgr{
public:
	ObjectMgr(const ObjectMgr& r) = delete;//�R�s�[�֎~
	ObjectMgr& operator=(const ObjectMgr& r) = delete;//����֎~
	static ObjectMgr& get();

	Mgr<IEffect> effect_;
	Mgr<IButton> button_;

	void init();

private:
	ObjectMgr();
};

extern ObjectMgr& obj;