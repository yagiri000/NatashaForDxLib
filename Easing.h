//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once
#include <iostream>
#include <functional>
#include "Abstract.h"
#include "Vector2.h"
#include "Color.h"

using EaseFuncPtr = std::function<double(double, double, double, double)>;

namespace Ease{
	//イージング曲線 Sinusoidal;
	double sinIn(double nowFrame, double allFrame, double start, double end);
	double sinOut(double nowFrame, double allFrame, double start, double end);
	double sinInOut(double nowFrame, double allFrame, double start, double end);
	//イージング曲線 Cubic;
	double cubicIn(double nowFrame, double allFrame, double start, double end);
	double cubicOut(double nowFrame, double allFrame, double start, double end);
	double cubicInOut(double nowFrame, double allFrame, double start, double end);
	//イージング曲線 Exponential;
	double expIn(double nowFrame, double allFrame, double start, double end);
	double expOut(double nowFrame, double allFrame, double start, double end);
	double expInOut(double nowFrame, double allFrame, double start, double end);
	//イージング曲線 Circular;
	double sqrtIn(double nowFrame, double allFrame, double start, double end);
	double sqrtOut(double nowFrame, double allFrame, double start, double end);
	double sqrtInOut(double nowFrame, double allFrame, double start, double end);
	//定数;
	double constant(double nowFrame, double allFrame, double start, double end);
	//線形に増加;
	double linear(double nowFrame, double allFrame, double start, double end);
	double sin010(double nowFrame, double allFrame, double startVal, double endVal);
	double linear010(double nowFrame, double allFrame, double startVal, double endVal);
	double sinNormal(double nowFrame, double TFrame, double base, double range);


	class Val{
	public:
		int eFrame;
		int endFrame;
		double startVal;
		double endVal;
		EaseFuncPtr easeFunc;
		Val();
		Val(double val);
		Val(int endFrame_, double startVal_, double endVal_, const EaseFuncPtr &easeFunc_);
		void set(int endFrame_, double startVal_, double endVal_);
		void set(int endFrame_, double startVal_, double endVal_, const EaseFuncPtr &easeFunc_);
		double operator()();
		double getVal();
		void update();
		void update(int eFrame_);
	};

	class Pos{
	public:
		int eFrame;
		int endFrame;
		Vector2 startPos;
		Vector2 endPos;
		EaseFuncPtr easeFunc;
		Pos();
		Pos(const Vector2 &pos_);
		Pos(int endFrame_, const Vector2 &startPos_, const Vector2 &endPos_, const EaseFuncPtr &easeFunc_);
		void set(int endFrame_, const Vector2 &startPos_, const Vector2 &endPos_);
		void set(int endFrame_, const Vector2 &startPos_, const Vector2 &endPos_, const EaseFuncPtr &easeFunc_);
		Vector2 operator()();
		Vector2 getVal();
		void update();
		void update(int eFrame_);
	};

	class Color{
	public:
		int eFrame;
		int endFrame;
		HSV startColor;
		HSV endColor;
		EaseFuncPtr easeFunc;
		Color();
		Color(size_t col_);
		Color(const HSV &col_);
		Color(int endFrame_, const HSV &startColor_, const HSV &endColor_, const EaseFuncPtr &easeFunc_);
		void set(int endFrame_, const HSV &startColor_, const HSV &endColor_);
		void set(int endFrame_, const HSV &startColor_, const HSV &endColor_, const EaseFuncPtr &easeFunc_);
		size_t operator()();
		size_t getVal();
		void update();
		void update(int eFrame_);
	};


	Val makeDifVal(int endFrame_, double start_, double dif_, const EaseFuncPtr &easeFunc_);
	Pos makeDifPos(int endFrame_, const Vector2 &start_, const Vector2 &dif_, const EaseFuncPtr &easeFunc_);
	Color makeDifColor(int endFrame_, const HSV &start_, const HSV &dif_, const EaseFuncPtr &easeFunc_);

	//終点とそこからの差を指定して作る
	Val makeRevVal(int endFrame_, double dif_, double end_, const EaseFuncPtr &easeFunc_);
	Pos makeRevPos(int endFrame_, const Vector2 &dif_, const Vector2 &end_, const EaseFuncPtr &easeFunc_);
	Color makeRevColor(int endFrame_, const HSV &dif_, const HSV &end_, const EaseFuncPtr &easeFunc_);
};