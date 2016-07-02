#include "Screen.h"
#include "DxLib.h"
#include "Func.h"


//IScreenEffect Impliment

class IScreenEffect : public IObject{
public:
	int eFrame;
	int allFrame;
	virtual void update();
	virtual void update_() = 0;
	virtual void draw() = 0;
	IScreenEffect(int allFrame_);
};

class ScreenEffectReverseHue : public IScreenEffect
{
public:
	virtual void update_();
	virtual void draw();
	ScreenEffectReverseHue(int allFrame_);
};


class ScreenEffectInvert : public IScreenEffect
{
public:
	virtual void update_();
	virtual void draw();
	ScreenEffectInvert(int allFrame_);
};

class ScreenEffectGauss : public IScreenEffect
{
public:
	Ease::Val gaussDist;
	virtual void update_();
	virtual void draw();
	ScreenEffectGauss(int allFrame_);
};

class ScreenEffectSaturation : public IScreenEffect
{
public:
	Ease::Val saturation;
	virtual void update_();
	virtual void draw();
	ScreenEffectSaturation(int allFrame_);
};

class ScreenEffectBlackOut : public IScreenEffect
{
public:
	Ease::Val brightness;
	virtual void update_();
	virtual void draw();
	ScreenEffectBlackOut(int allFrame_);
};

class ScreenEffectWhiteOut : public IScreenEffect
{
public:
	Ease::Val brightness;
	virtual void update_();
	virtual void draw();
	ScreenEffectWhiteOut(int allFrame_);
};

class ScreenEffectTransition : public IScreenEffect
{
public:
	Ease::Val gaussDist;
	Ease::Val brightness;
	virtual void update_();
	virtual void draw();
	ScreenEffectTransition(int allFrame_);
};



//ScreenDraw Impliment

class IScreenDraw : public IObject{
public:
	int eFrame;
	int allFrame;
	IScreenDraw(int allFrame_);
	virtual void update();
	virtual void update_() = 0;
	virtual void draw() = 0;
};

class ScreenDrawShake : public IScreenDraw{
public:
	double shakeDistance;//�h��鋗��
	ScreenDrawShake(int allFrame_);
	ScreenDrawShake(int allFrame_, double shakeDistance_);
	virtual void update_();
	virtual void draw();
};

class ScreenDrawExtend : public IScreenDraw{
public:
	Ease::Val exRate;
	ScreenDrawExtend(int allFrame_);
	virtual void update_();
	virtual void draw();
};


IScreenEffect::IScreenEffect(int allFrame_) :
eFrame(0),
allFrame(allFrame_)
{
}

void IScreenEffect::update(){
	update_();
	eFrame++;
	IsDead = eFrame > allFrame;
}

ScreenEffectReverseHue::ScreenEffectReverseHue(int allFrame_) :
IScreenEffect(allFrame_)
{
}

void ScreenEffectReverseHue::update_(){
}

void ScreenEffectReverseHue::draw(){
	Screen::HSB(0, 180, 0, 0);
}

ScreenEffectInvert::ScreenEffectInvert(int allFrame_) :
IScreenEffect(allFrame_)
{
}

void ScreenEffectInvert::update_(){
}

void ScreenEffectInvert::draw(){
	Screen::Invert();
}



ScreenEffectGauss::ScreenEffectGauss(int allFrame_) :
IScreenEffect(allFrame_),
gaussDist(Ease::Val(allFrame_, 0, 1000, Ease::sin010))
{
}

void ScreenEffectGauss::update_(){
	gaussDist.update();
}

void ScreenEffectGauss::draw(){
	Screen::Gauss(8, gaussDist());
}


ScreenEffectSaturation::ScreenEffectSaturation(int allFrame_) :
IScreenEffect(allFrame_),
saturation(Ease::Val(allFrame_, 0, -255, Ease::sin010))
{
}

void ScreenEffectSaturation::update_(){
	saturation.update();
}

void ScreenEffectSaturation::draw(){
	Screen::HSB(0, 0, saturation(), 0);
}

ScreenEffectBlackOut::ScreenEffectBlackOut(int allFrame_) :
IScreenEffect(allFrame_),
brightness(Ease::Val(allFrame_, 0, -255, Ease::sin010))
{
}

void ScreenEffectBlackOut::update_(){
	brightness.update();
}

void ScreenEffectBlackOut::draw(){
	Screen::HSB(0, 0, 0, brightness());
}

ScreenEffectWhiteOut::ScreenEffectWhiteOut(int allFrame_) :
IScreenEffect(allFrame_),
brightness(Ease::Val(allFrame_, 0, 255, Ease::sin010))
{
}

void ScreenEffectWhiteOut::update_(){
	brightness.update();
}

void ScreenEffectWhiteOut::draw(){
	Screen::HSB(0, 0, 0, brightness());
}

ScreenEffectTransition::ScreenEffectTransition(int allFrame_) :
IScreenEffect(allFrame_),
gaussDist(Ease::Val(allFrame_, 0, 1000, Ease::sin010)),
brightness(Ease::Val(allFrame_, 0, -255, Ease::sin010))
{
}

void ScreenEffectTransition::update_(){
	gaussDist.update();
	brightness.update();
}

void ScreenEffectTransition::draw(){
	Screen::Gauss(8, gaussDist());
	Screen::HSB(0, 0, 0, brightness());
}



IScreenDraw::IScreenDraw(int allFrame_) :
eFrame(0),
allFrame(allFrame_)
{
}

void IScreenDraw::update(){
	update_();
	eFrame++;
	IsDead = eFrame > allFrame;
}


ScreenDrawShake::ScreenDrawShake(int allFrame_) :
IScreenDraw(allFrame_),
shakeDistance(10)
{
}

ScreenDrawShake::ScreenDrawShake(int allFrame_, double shakeDistance_) :
IScreenDraw(allFrame_),
shakeDistance(shakeDistance_)
{
}

void ScreenDrawShake::update_(){
}

void ScreenDrawShake::draw(){
	double dx, dy;
	Random::RandInCircle(shakeDistance, dx, dy);
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawGraph(dx, dy, Screen::get().mainScreen, FALSE);
}


ScreenDrawExtend::ScreenDrawExtend(int allFrame_) :
IScreenDraw(allFrame_),
exRate(Ease::Val(allFrame_, 2.0, 1.0, Ease::linear))
{
}

void ScreenDrawExtend::update_(){
	exRate.update();
}

void ScreenDrawExtend::draw(){
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRotaGraph2(ScreenWidth / 2.0, ScreenHeight / 2.0, ScreenWidth / 2.0, ScreenHeight / 2.0, exRate(), 0.0, Screen::get().mainScreen, FALSE);
}


ScreenDrawEffectMgr::ScreenDrawEffectMgr()
{
}

void ScreenDrawEffectMgr::addEffect(const std::shared_ptr<IScreenEffect> &ptr){
	effectList.emplace_back(ptr);
}

void ScreenDrawEffectMgr::addDraw(const std::shared_ptr<IScreenDraw> &ptr){
	drawObj = ptr;
}

void ScreenDrawEffectMgr::update(){
	for (auto &i = effectList.begin(); i < effectList.end(); i++){
		(**i).update();
	}
	//IsDead��true�Ȃ珜��
	auto rmv = std::remove_if(effectList.begin(), effectList.end(),
		[](std::shared_ptr<IScreenEffect> p)->bool{
		return p->IsDead;
	}
	);
	effectList.erase(rmv, effectList.end());

	if (drawObj != nullptr){
		drawObj->update();
		if (drawObj->IsDead){
			drawObj = nullptr;
		}
	}
}

void ScreenDrawEffectMgr::draw(){
	for (auto &i = effectList.begin(); i < effectList.end(); i++){
		(**i).draw();
	}

	if (drawObj == nullptr){
		SetDrawScreen(DX_SCREEN_BACK);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawGraph(0, 0, Screen::get().mainScreen, FALSE);
	}
	else{
		drawObj->draw();
	}
}


Screen& Screen::get(){
	static Screen inst;
	return inst;
}

//���t���[���F�����]
void Screen::setReverseHue(int frame){
	Screen::get().screenDrawEffectMgr.addEffect(std::make_shared<ScreenEffectReverseHue>(frame));
}

//���t���[���F���]
void Screen::setInvert(int frame){
	Screen::get().screenDrawEffectMgr.addEffect(std::make_shared<ScreenEffectInvert>(frame));
}

//���t���[���K�E�X
void Screen::setGauss(int frame){
	Screen::get().screenDrawEffectMgr.addEffect(std::make_shared<ScreenEffectGauss>(frame));
}

//���t���[���Ó]
void Screen::setBlackOut(int frame){
	Screen::get().screenDrawEffectMgr.addEffect(std::make_shared<ScreenEffectBlackOut>(frame));
}

//���t���[���Ó]
void Screen::setWhiteOut(int frame){
	Screen::get().screenDrawEffectMgr.addEffect(std::make_shared<ScreenEffectWhiteOut>(frame));
}

//���t���[���Ó]
void Screen::setSaturation(int frame){
	Screen::get().screenDrawEffectMgr.addEffect(std::make_shared<ScreenEffectSaturation>(frame));
}

// ���t���[���A�K�E�X���Ó]
void Screen::setTransition(int frame){
	Screen::get().screenDrawEffectMgr.addEffect(std::make_shared<ScreenEffectTransition>(frame));
}

//�X�N���[���h���ݒ�
void Screen::setShake(int frame, int distance){
	Screen::get().screenDrawEffectMgr.addDraw(std::make_shared<ScreenDrawShake>(frame, distance));
}

// �X�N���[���g�嗦2.0 > 1.0��
void Screen::setExtendScreen(int frame){
	Screen::get().screenDrawEffectMgr.addDraw(std::make_shared<ScreenDrawExtend>(frame));
}

// �K�E�X�t�B���^�[���{��
void Screen::Gauss(int pal_1, int pal_2){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_GAUSS, pal_1, pal_2);
}

// HSB�t�B���^�[���{��
void Screen::HSB(int type, int hue, int saturation, int bright){
	if (type == 0){
		hue %= 360;
		if (hue < -180){
			hue += 360;
		}
		if (hue > 180){
			hue -= 360;
		}
	}
	else{
		hue %= 360;
		if (hue < 0){
			hue += 360;
		}
	}
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_HSB, type, hue, saturation, bright);
}

// �K�����]�t�B���^�[���{��
void Screen::Invert(){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_INVERT);
}

// Level�t�B���^�[���{��
void Screen::Level(int min, int max, int gamma, int afterMin, int afterMax){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_LEVEL, min, max, gamma, afterMin, afterMax);
}

// �O���f�[�V�����}�b�v�t�B���^�[���{��
void Screen::GradiendMap(int handle){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_GRADIENT_MAP, handle, FALSE);
}

//�`��J�n
void Screen::DrawStart(){
	SetDrawScreen(get().mainScreen);
	ClearDrawScreen();
}

//�V�F�[�_�[�Ƃ��K�p���鎞�p
void Screen::SetDrawScreenSub(){
	SetDrawScreen(get().subScreen);
}

//�V�F�[�_�[�Ƃ��K�p�������Ɨp
void Screen::SetDrawScreenMain(){
	SetDrawScreen(get().mainScreen);
}

//�`��I���E�t���b�v
void Screen::DrawEnd(){
	get().screenDrawEffectMgr.update();
	get().screenDrawEffectMgr.draw();

	ScreenFlip();
}


//�c�����C���[�Ɍ��݂̃��C���[���R�s�[
void Screen::SetAfterImageScreen(){
	SetDrawScreen(get().afterImageScreen);
	ClearDrawScreen();
	GraphFilterBlt(get().mainScreen, get().afterImageScreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
	get().afterImageAlpha = 255;
	SetDrawScreen(get().mainScreen);
}

//�c�����C���[��`��
void Screen::DrawAfterImageScreen(){
	if (get().afterImageAlpha >= 0){
		GraphFilter(get().afterImageScreen, DX_GRAPH_FILTER_GAUSS, 8, 100);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, get().afterImageAlpha);
		DrawGraph(0, 0, get().afterImageScreen, TRUE);
		get().afterImageAlpha -= 5;
	}
}

Screen::Screen() :
width(1024),
height(1024),
afterImageAlpha(0)
{
	init();
}

void Screen::init(){
	//�V���ɃX�N���[�����쐬
	mainScreen = MakeScreen(width, height, 1);
	afterImageScreen = MakeScreen(width, height, 1);
	tmpScreen = MakeScreen(width, height, 1);
	subScreen = MakeScreen(width, height, 1);
	scopeScreen = MakeScreen(128, 128, 0);
}


