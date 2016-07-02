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

//各オブジェクトをスマートポインタの形で所持しているだけのクラス（シングルトン）
class ObjectMgr{
public:
	ObjectMgr(const ObjectMgr& r) = delete;//コピー禁止
	ObjectMgr& operator=(const ObjectMgr& r) = delete;//代入禁止
	static ObjectMgr& get();

	Mgr<IEffect> effect_;
	Mgr<IButton> button_;

	void init();

private:
	ObjectMgr();
};

extern ObjectMgr& obj;