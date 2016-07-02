//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once

#include <string>
#include <deque>
#include "Abstract.h"
#include "Easing.h"

//pImpl
class IScreenEffect;
class IScreenDraw;

class ScreenDrawEffectMgr{
public:
	std::vector<std::shared_ptr<IScreenEffect>> effectList;
	std::shared_ptr<IScreenDraw> drawObj;
	ScreenDrawEffectMgr();
	void addEffect(const std::shared_ptr<IScreenEffect> &ptr);
	void addDraw(const std::shared_ptr<IScreenDraw> &ptr);
	void update();
	void draw();
};

class Screen{
public:
	//シングルトン
	Screen& operator=(const Screen& a) = delete;
	Screen(const Screen& a) = delete;
	static Screen& get();

	//スクリーンサイズ
	const int width;
	const int height;

	int afterImageAlpha;

	//スクリーン
	int mainScreen;		//主にこれに描画する
	int afterImageScreen;//残像用レイヤー
	int tmpScreen;
	int subScreen; //シェーダー適用用
	int scopeScreen;

	ScreenDrawEffectMgr screenDrawEffectMgr;

	//一定フレーム色相反転
	static void setReverseHue(int frame);

	//一定フレーム反転
	static void setInvert(int frame);

	//一定フレームガウス
	static void setGauss(int frame);

	//一定フレーム暗転
	static void setBlackOut(int frame);

	//一定フレーム白転
	static void setWhiteOut(int frame);

	//一定フレーム彩度下げる
	static void setSaturation(int frame);
	
	//一定フレーム暗転＆ガウス
	static void setTransition(int frame);

	//指定フレームスクリーンを拡大して縮小する
	static void setExtendScreen(int frame);

	//スクリーン揺れを設定
	static void setShake(int frame, int distance = 20);

	// ガウスフィルターを施す
	static void Gauss(int pal_1 = 8, int pal_2 = 1000);

	// HSBフィルターを施す
	static void HSB(int type, int hue, int saturation, int bright);

	// 階調反転フィルターを施す
	static void Invert();

	// Levelフィルターを施す
	static void Level(int min, int max, int gamma, int afterMin, int afterMax);

	// グラデーションマップフィルターを施す
	static void GradiendMap(int handle);

	//描画開始
	static void DrawStart();

	//シェーダーとか適用する時用
	static void SetDrawScreenSub();

	//シェーダーとか適用したあと用
	static void SetDrawScreenMain();

	//描画終了・フリップ
	static void DrawEnd();


	//残像レイヤーに現在のレイヤーをコピー
	static void SetAfterImageScreen();

	//残像レイヤーを描画
	static void DrawAfterImageScreen();

private:
	Screen();
	void init();
};


