#include <iostream>
#include "Easing.h"
#include "myglobal.h"
#include <functional>

namespace Ease{

	//イージング曲線 Sinusoidal
	double sinIn(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			return start + (end - start) * (1.0 - sin(PI / 2 * (1.0 - nowFrame / allFrame)));
		}
		else{
			return end;
		}
	}

	double sinOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			return start + (end - start) * sin(PI / 2 * nowFrame / allFrame);
		}
		else{
			return end;
		}
	}

	double sinInOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			return -(end - start) / 2.0 * (cos(PI * nowFrame / allFrame) - 1) + start;
		}
		else{
			return end;
		}
	}


	//イージング曲線 Cubic
	double cubicIn(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			nowFrame /= allFrame;
			return (end - start) * pow(nowFrame, 3.0) + start;
		}
		else{
			return end;
		}
	}

	double cubicOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			nowFrame /= allFrame;
			nowFrame = nowFrame - 1;
			return (end - start) * (pow(nowFrame, 3.0) + 1) + start;
		}
		else{
			return end;
		}
	}

	double cubicInOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			nowFrame /= allFrame / 2.0;
			if (nowFrame < 1){
				return (end - start) / 2.0 * pow(nowFrame, 3.0) + start;
			}
			else{
				nowFrame = nowFrame - 2;
				return (end - start) / 2.0 * (pow(nowFrame, 3.0) + 2) + start;
			}
		}
		else{
			return end;
		}
	}


	//イージング曲線 Exponential
	double expIn(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			return (end - start) * pow(2.0, (10 * (nowFrame / allFrame - 1))) + start;
		}
		else{
			return end;
		}
	}

	double expOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			return (end - start) * (-(pow(2.0, (-10.0 * nowFrame / allFrame))) + 1) + start;
		}
		else{
			return end;
		}
	}

	double expInOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			nowFrame /= allFrame / 2.0;
			if (nowFrame < 1){
				return (end - start) / 2.0 * pow(2.0, (10.0 * (nowFrame - 1))) + start;
			}
			else{
				nowFrame = nowFrame - 1;
				return (end - start) / 2.0 * (-(pow(2.0, (-10 * nowFrame))) + 2) + start;
			}
		}
		else{
			return end;
		}
	}



	//イージング曲線 Circular
	double sqrtIn(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			nowFrame /= allFrame;
			return -(end - start) * (sqrt(1 - nowFrame * nowFrame) - 1) + start;
		}
		else{
			return end;
		}
	}

	double sqrtOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			nowFrame /= allFrame;
			nowFrame = nowFrame - 1;
			return (end - start) * sqrt(1 - nowFrame*nowFrame) + start;
		}
		else{
			return end;
		}
	}

	double sqrtInOut(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			nowFrame /= allFrame / 2.0;
			if (nowFrame < 1){
				return -(end - start) / 2.0 * (sqrt(1 - nowFrame*nowFrame) + 1);
			}
			else{
				nowFrame = nowFrame - 2;
				return (end - start) / 2.0 * (sqrt(1 - nowFrame*nowFrame) + 1) + start;
			}
		}
		else{
			return end;
		}
	}

	//定数
	double constant(double nowFrame, double allFrame, double start, double end){
		return end;
	}

	//線形に増加
	double linear(double nowFrame, double allFrame, double start, double end){
		if (nowFrame < 0){
			return start;
		}
		else if (nowFrame < allFrame){
			return start + (end - start) * (nowFrame / allFrame);
		}
		else{
			return end;
		}
	}

	//0->1->0と変化するグラフ
	double sin010(double nowFrame, double allFrame, double min, double max){
		if (nowFrame < 0){
			return min;
		}
		else if (nowFrame < allFrame){
			return min + (max - min) * sin(PI * (nowFrame / allFrame));
		}
		else{
			return min;
		}
	}

	//0->1->0と変化するグラフ
	double linear010(double nowFrame, double allFrame, double min, double max){
		if (nowFrame < 0){
			return min;
		}
		else if (nowFrame < allFrame){
			return min + (max - min) * (1.0 - abs(1.0 - 2.0 * (nowFrame / allFrame)));
		}
		else{
			return min;
		}
	}

	//普通のsin(他の名前空間に移動するべきか）
	double sinNormal(double nowFrame, double TFrame, double base, double range){
		return base + range * sin(2 * PI * (nowFrame / TFrame) - PI / 4);
	}

	Val::Val() :
		eFrame(0),
		endFrame(0),
		startVal(0),
		endVal(0),
		easeFunc(sinOut)
	{
	}

	Val::Val(double val) :
		eFrame(0),
		endFrame(0),
		startVal(val),
		endVal(val),
		easeFunc(sinOut)
	{
	}

	Val::Val(int endFrame_, double startVal_, double endVal_, const EaseFuncPtr &easeFunc_) :
		eFrame(0),
		endFrame(endFrame_),
		startVal(startVal_),
		endVal(endVal_),
		easeFunc(easeFunc_)
	{
	}

	void Val::set(int endFrame_, double startVal_, double endVal_){
		eFrame = 0;
		endFrame = endFrame_;
		startVal = startVal_;
		endVal = endVal_;
	}

	void Val::set(int endFrame_, double startVal_, double endVal_, const EaseFuncPtr &easeFunc_){
		eFrame = 0;
		endFrame = endFrame_;
		startVal = startVal_;
		endVal = endVal_;
		easeFunc = easeFunc_;
	}

	double Val::operator()(){
		return getVal();
	}

	double Val::getVal(){
		return easeFunc(eFrame, endFrame, startVal, endVal);
	}

	void Val::update(){
		eFrame++;
	}

	void Val::update(int eFrame_){
		eFrame = eFrame_;
	}


	Pos::Pos() :
		eFrame(0),
		endFrame(0),
		startPos(),
		endPos(),
		easeFunc(sinOut)
	{
	}

	Pos::Pos(const Vector2 &pos_) :
		eFrame(0),
		endFrame(0),
		startPos(pos_),
		endPos(pos_),
		easeFunc(sinOut)
	{
	}

	Pos::Pos(int endFrame_, const Vector2 &startPos_, const Vector2 &endPos_, const EaseFuncPtr &easeFunc_) :
		eFrame(0),
		endFrame(endFrame_),
		startPos(startPos_),
		endPos(endPos_),
		easeFunc(easeFunc_)
	{
	}

	void Pos::set(int endFrame_, const Vector2 &startPos_, const Vector2 &endPos_){
		eFrame = 0;
		endFrame = endFrame_;
		startPos = startPos_;
		endPos = endPos_;
	}

	void Pos::set(int endFrame_, const Vector2 &startPos_, const Vector2 &endPos_, const EaseFuncPtr &easeFunc_){
		eFrame = 0;
		endFrame = endFrame_;
		startPos = startPos_;
		endPos = endPos_;
		easeFunc = easeFunc_;
	}

	Vector2 Pos::operator()(){
		return getVal();
	}

	Vector2 Pos::getVal(){
		return startPos * (1.0 - easeFunc(eFrame, endFrame, 0.0, 1.0)) + endPos * easeFunc(eFrame, endFrame, 0.0, 1.0);
	}

	void Pos::update(){
		eFrame++;
	}

	void Pos::update(int eFrame_){
		eFrame = eFrame_;
	}

	Color::Color() :
		eFrame(0),
		endFrame(0),
		startColor(),
		endColor(),
		easeFunc(sinOut)
	{
	}


	Color::Color(size_t col_) :
		eFrame(0),
		endFrame(0),
		startColor(col_),
		endColor(col_),
		easeFunc(sinOut)
	{
	}


	Color::Color(const HSV &col_) :
		eFrame(0),
		endFrame(0),
		startColor(col_),
		endColor(col_),
		easeFunc(sinOut)
	{
	}


	Color::Color(int endFrame_, const HSV &startColor_, const HSV &endColor_, const EaseFuncPtr &easeFunc_) :
		eFrame(0),
		endFrame(endFrame_),
		startColor(startColor_),
		endColor(endColor_),
		easeFunc(easeFunc_)
	{
	}

	void Color::set(int endFrame_, const HSV &startColor_, const HSV &endColor_){
		eFrame = 0;
		endFrame = endFrame_;
		startColor = startColor_;
		endColor = endColor_;
	}

	void Color::set(int endFrame_, const HSV &startColor_, const HSV &endColor_, const EaseFuncPtr &easeFunc_){
		eFrame = 0;
		endFrame = endFrame_;
		startColor = startColor_;
		endColor = endColor_;
		easeFunc = easeFunc_;
	}

	size_t Color::operator()(){
		return getVal();
	}

	size_t Color::getVal(){
		return (startColor * (1.0 - easeFunc(eFrame, endFrame, 0.0, 1.0)) + endColor * easeFunc(eFrame, endFrame, 0.0, 1.0))();
	}

	void Color::update(){
		eFrame++;
	}

	void Color::update(int eFrame_){
		eFrame = eFrame_;
	}


	Val makeDifVal(int endFrame_, double start_, double dif_, const EaseFuncPtr &easeFunc_){
		return Val(endFrame_, start_, start_ + dif_, easeFunc_);
	}

	Pos makeDifPos(int endFrame_, const Vector2 &start_, const Vector2 &dif_, const EaseFuncPtr &easeFunc_){
		return Pos(endFrame_, start_, start_ + dif_, easeFunc_);
	}

	Color makeDifColor(int endFrame_, const HSV &start_, const HSV &dif_, const EaseFuncPtr &easeFunc_){
		return Color(endFrame_, start_, start_ + dif_, easeFunc_);
	}

	Val makeRevVal(int endFrame_, double dif_, double end_, const EaseFuncPtr &easeFunc_){
		return Val(endFrame_, end_ + dif_, end_, easeFunc_);
	}

	Pos makeRevPos(int endFrame_, const Vector2 &dif_, const Vector2 &end_, const EaseFuncPtr &easeFunc_){
		return Pos(endFrame_, end_ + dif_, end_, easeFunc_);
	}

	Color makeRevColor(int endFrame_, const HSV &dif_, const HSV &end_, const EaseFuncPtr &easeFunc_){
		return Color(endFrame_, end_ + dif_, end_, easeFunc_);
	}
};