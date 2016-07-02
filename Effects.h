//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------

//-------------------------------------------
//                n. i. a.
//                         Effect Draw System
//-------------------------------------------

#pragma once

#include <vector>
#include <functional>

#include "Abstract.h"
#include "Vector2.h"
#include "Easing.h"


class IEffect : public IObject{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
};

//エフェクトの基底クラス：開始の値と終了の値・補完関数を持つEaseクラスを持ち、時間に従ってパラメータを更新する
class IEaseEffect : public IEffect{
public:
	Ease::Pos pos;
	Ease::Pos exRate;
	Ease::Val angle;
	Ease::Val alpha;
	int blendMode;
	int gHandle;
	Vector2 center;
	int turnFlag;
	int eFrame;
	int deleteFrame;

	IEaseEffect();
	IEaseEffect(const Ease::Pos &pos_, const Ease::Pos &exRate_, const Ease::Val &angle_, const Ease::Val &alpha_, int blendMode_, int gHandle_, int turnFlag_, int deleteFrame_);


	//update内で毎フレーム呼ばれる、追加機能のための関数（元は中身なし）
	virtual void additionalFunc();
	//オブジェクト破棄の際に呼ばれる、追加機能のための関数（元は中身なし）
	virtual void dyingFunc();
	virtual void update_();

	//eFrameを更新し、update_() を呼び、適宜他の追加機能関数を呼ぶ
	void update();
	virtual void draw();
};

//エフェクトの基底クラス：値を加算していき、パラメータを更新する、単純なクラス
class IVelEffect : public IEffect{
public:
	Vector2 pos;
	Vector2 center;
	Vector2 exRate;
	double angle;

	double alpha;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 exRatePlus;
	double speedRate;

	double anglePlus;
	double alphaPlus;
	int turnFlag;
	int blendMode;

	int ghandle;

	int elapsedFrame;
	int deleteFrame;

	double PI;

	IVelEffect();


	virtual void set(
		const Vector2 &pos,
		const Vector2 &center,
		const Vector2 &exRate,
		double angle,

		double alpha,
		const Vector2 &velocity,
		const Vector2 &acceleration,
		const Vector2 &exRatePlus,
		double speedRate,

		double anglePlus,
		double alphaPlus,
		int turnFlag,
		int blendMode,

		int ghandle,

		int deleteFrame
		);

	virtual void move();
	virtual void update();
	virtual void draw();
};



class Hoge : public IVelEffect{
public:
	Hoge(const Vector2 &pos);
};

class AlphaZero : public IVelEffect{
public:
	AlphaZero(const Vector2 &pos);
};

class AlphaSin : public IVelEffect{
public:
	AlphaSin(const Vector2 &pos);
	virtual void move();
};

class MakeAlphaZeroOnLine : public IVelEffect{
public:
	MakeAlphaZeroOnLine(const Vector2 &pos);
	virtual void move();
};

class MakeAlphaZeroOnCircle : public IVelEffect{
public:
	MakeAlphaZeroOnCircle(const Vector2 &pos);
	virtual void move();
};