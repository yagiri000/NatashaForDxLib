//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once

#include <DxLib.h>
#include <iostream>

#include "myglobal.h"
#include "Vector2.h"



namespace HorizontalPlace{
	enum en{
		left,
		center,
		right,
	};
}
namespace VerticalPlace{
	enum en{
		top,
		center,
		bottom,
	};
}

//シングルトンDrawクラス
class DrawImpl
{
public:
	DrawImpl();

	double dx;
	double dy;
	Vector2 shiftVec;

	struct TextDrawLog{
		Vector2 pos;
		int color;
		int fontHandle;
		int alpha;
		int blendMode;
		const int yDif = 20;
		void set(const Vector2 &pos_, int color_, int fontHandle_, int alpha_, int blendMode_);
	};
	TextDrawLog textDrawLog;

	//描画する座標のシフト量を設定
	void setdxdy(int x, int y);

	//画像の左上の座標を指定して描画
	void normal(const Vector2& pos, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//画像の中央の座標を指定して描画
	void center(const Vector2& pos, int gHandle, int alpha, int turnFlag = 0, int blendMode = DX_BLENDMODE_ALPHA);

	//拡大・回転描画
	void exrot(const Vector2& pos, double ExtRate, double angle, int gHandle, int alpha, int turnFlag = 0, int blendMode = DX_BLENDMODE_ALPHA);

	//拡大・回転・中央指定描画
	void exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double angle, int gHandle, int alpha, int turnFlag = 0, int blendMode = DX_BLENDMODE_ALPHA);
	
	//3次元回転描画
	void rot3D(const Vector2& pos, const Vector2& exRate, float zRot, float xRot, float yRot, int gHandle, int turnFlag = 0);

	//自由変形描画
	void modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//左上・右下を指定して描画
	void modi2(const Vector2& pos1, const Vector2& pos2, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//楕円上にグラフを描画　rで円の半径・rate:縦にrをrateの比の分ひしゃげさせる・angle:回転角
	void modiOval(const Vector2& pos, double r, double rate, double angle, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
	void trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int gHandle, int alpha, int turnFlag = 0, int blendMode = DX_BLENDMODE_ALPHA);

	//サークルゲージ描画　(dx, dy)分シフト
	void circleGauge(const Vector2& pos, double percent, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//サークルゲージ描画（逆方向）　(dx, dy)分シフト
	void circleGaugeReverse(const Vector2& pos, double percent, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//図形描画関数
	//線を描画
	void line(const Vector2& start_pos, const Vector2& end_pos, int color, int alpha, int thickness = 1, int blendMode = DX_BLENDMODE_ALPHA);

	//始点と終点への距離、角度を指定して線を描画
	void lineAngle(const Vector2& start_pos, int r, double angle, int color, int alpha, int thickness = 1, int blendMode = DX_BLENDMODE_ALPHA);

	//箱を描画
	void box(const Vector2& pos1, const Vector2& pos2, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//中心を指定して箱を描画
	void centerBox(const Vector2& center_pos, const Vector2& size, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//円を描画
	void circle(const Vector2& pos, int r, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//円を描画
	void circleRing(const Vector2& pos, int r, int ringWidth, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//三角形を描画
	void triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//文字描画関数
	void text(const Vector2& pos, int color, int fonthandle, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//文字描画関数
	void normalText(const Vector2& pos, const std::string &str);

	//文字描画関数
	void normalTextBox(const Vector2& pos, const std::string &str);

	//文字を描画
	void textPlace(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh = HorizontalPlace::left, VerticalPlace::en fv = VerticalPlace::top, int blendMode = DX_BLENDMODE_ALPHA);

	//文字を描画・位置指定
	void textPlaceSpace(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, double space, HorizontalPlace::en fh = HorizontalPlace::left, VerticalPlace::en fv = VerticalPlace::top, int blendMode = DX_BLENDMODE_ALPHA);

	//文字を描画・文字の背景に箱を描画
	void textBox(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh, VerticalPlace::en fv, const Vector2 &boxMargeV2, int boxColor, int boxAlpha, int blendMode = DX_BLENDMODE_ALPHA, int boxBlendMode = DX_BLENDMODE_ALPHA);

	//前回書いた文字の次の行に文字を描画
	void textNextLine(const std::string &str);

	//複数行に文字を描画・"\n"で改行
	void textLine(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh = HorizontalPlace::left, VerticalPlace::en fv = VerticalPlace::top, int blendMode = DX_BLENDMODE_ALPHA);

	//指定した座標を中心に文字を描画
	void centerText(const Vector2& pos, int color, int fonthandle, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//文字の右上の座標を指定して文字を描画
	void rightText(const Vector2& pos, int color, int fonthandle, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//指定した座標を中心に文字を描画 文字の間隔を指定可能
	void textSpace(const Vector2& pos, int color, int fonthandle, int space, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);
	
	//指定した座標を中心に文字を描画 文字の間隔を指定可能
	void centerTextSpace(const Vector2& pos, int color, int fonthandle, int space, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//指定した座標を中心に文字を描画 文字の間隔を指定可能
	void rightTextSpace(const Vector2& pos, int color, int fonthandle, int space, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

};


extern DrawImpl Draw;
extern DrawImpl DrawAbs;