//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------

//-------------------------------------------
//
//                n. i. a.
//
//                         Effect Draw System
//-------------------------------------------

#include "GameMgr.h"
#include "Resource.h"
#include "Func.h"
#include "Draw.h"


IEaseEffect::IEaseEffect()
{
}

IEaseEffect::IEaseEffect(const Ease::Pos &pos_, const Ease::Pos &exRate_, const Ease::Val &angle_, const Ease::Val &alpha_, int blendMode_, int gHandle_, int turnFlag_, int deleteFrame_) :
pos(pos_),
exRate(exRate_),
angle(angle_),
alpha(alpha_),
blendMode(blendMode_),
gHandle(gHandle_),
center(Func::getGraphSizeV2(gHandle_) * 0.5),
turnFlag(turnFlag_),
eFrame(0),
deleteFrame(deleteFrame_)
{

}

void IEaseEffect::update(){
	eFrame++;
	update_();
	additionalFunc();
	if (eFrame > deleteFrame){
		dyingFunc();
		IsDead = true;
	}
}

void IEaseEffect::additionalFunc(){
}

void IEaseEffect::dyingFunc(){
}

void IEaseEffect::update_(){
	pos.update();
	exRate.update();
	angle.update();
	alpha.update();
}

void IEaseEffect::draw(){
	Draw.exrot3(pos(), center, exRate(), angle(), gHandle, alpha(), turnFlag, blendMode);
}




IVelEffect::IVelEffect() :
PI(3.141592653589793),
elapsedFrame(0)
{
}

void IVelEffect::set(
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
	)
{
	this->pos = pos;
	this->center = center;
	this->exRate = exRate;
	this->angle = angle;
	this->alpha = alpha;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->exRatePlus = exRatePlus;
	this->speedRate = speedRate;
	this->anglePlus = anglePlus;
	this->alphaPlus = alphaPlus;
	this->turnFlag = turnFlag;
	this->blendMode = blendMode;
	this->ghandle = ghandle;
	this->deleteFrame = deleteFrame;
}

void IVelEffect::move(){
	pos += velocity;
	velocity += acceleration;

	velocity *= speedRate;

	exRate += exRatePlus;

	angle += anglePlus;
	alpha += alphaPlus;
}

void IVelEffect::update(){
	if (elapsedFrame > -1){
		move();
	}

	elapsedFrame++;

	if (elapsedFrame > deleteFrame){
		IsDead = true;
	}
}

void IVelEffect::draw(){
	Draw.exrot3(pos, center, exRate, angle, ghandle, alpha, turnFlag, blendMode);
}

Hoge::Hoge(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), 0.0,
		255.0, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, 0, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 10);
};

AlphaZero::AlphaZero(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), 0.0,
		255.0, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, -255.0/25.0, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 25);
};

AlphaSin::AlphaSin(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), 0.0,
		255.0, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, 0, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 100);
	velocity = Random::RandOnCircle(2.0, 4.0);
};

void AlphaSin::move(){
	pos += velocity;
	velocity += acceleration;
	velocity *= speedRate;
	exRate += exRatePlus;
	angle += anglePlus;
	alpha = 128 + 128 * sin(elapsedFrame * 0.8);
}

MakeAlphaZeroOnLine::MakeAlphaZeroOnLine(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), 0.0,
		255.0, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, 0, 0, DX_BLENDMODE_ALPHA, 0, 100);
	velocity = Random::RandOnCircle(5.0, 10.0);
};

void MakeAlphaZeroOnLine::move(){
	pos += velocity;
	velocity += acceleration;

	velocity *= speedRate;

	exRate += exRatePlus;

	angle += anglePlus;
	alpha = alphaPlus;

	//mgr.effect_.add(std::make_shared<AlphaZero>(pos + Random::RandInCircle(32.0)));
}

MakeAlphaZeroOnCircle::MakeAlphaZeroOnCircle(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), 0.0,
		255.0, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, 0, 0, DX_BLENDMODE_ALPHA, 0, 1);
};

void MakeAlphaZeroOnCircle::move(){
	pos += velocity;
	velocity += acceleration;

	velocity *= speedRate;

	exRate += exRatePlus;

	angle += anglePlus;
	alpha = alphaPlus;

	for (int i = 0; i < 60; i++){
		//mgr.effect_.add(std::make_shared<AlphaZero>(pos + Random::RandInCircle(128)));
	}
}


