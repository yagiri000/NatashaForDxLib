#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <tuple>

#include "Abstract.h"
#include "Func.h"



//色を表すクラス(hue = 0~360)
struct HSV360
{
	HSV360(double, double, double);
	void set(double, double, double);
	DWORD GetRGB();
	double h;
	double s;
	double v;
};

//ボタンクラス群の基底クラス
class IButton : public IObject
{
public:
	Vector2 pos;
	Vector2 size;
	std::string label;
	std::function<void(void)> func;
	HSV360 boxHSV360;
	double boxAlpha;
	int fontColor;
	std::string fontName;
	bool isOnMouse;
	bool isClicked;
	bool isClicking;
	bool isClickEnd;//マウスが離された
	bool isPushing;

	IButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_);

	virtual void checkMouse();
	virtual void moveColor();
	virtual void die();
	virtual void update() = 0;
	virtual void draw();
};

//文字列を表示する（機能なし）
class Label : public IButton
{
public:
	Label(const Vector2 &pos_, Vector2 size_, std::string label_);
	void update();
};

//ボタンが押された時、指定された処理を実行する
class ClickButton : public IButton
{
public:
	ClickButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_);
	void update();
	void draw();
};

//ボタンが押されている間、指定された処理を実行する
class ClickingButton : public IButton
{
public:
	ClickingButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_);
	void moveColor();
	void update();
	void draw();
};

//ボタンがOnの間指定された処理を実行する
class OnOffButton : public IButton
{
public:
	bool isOn;//ボタンがオンかどうか
	OnOffButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_);
	void update();
	void draw();
};

//intへの参照をとり、ボタンクリックで値を更新する
class PlusMinusButton : public IButton
{
public:
	std::vector<std::shared_ptr<ClickButton>> click_vec;
	int &target;
	PlusMinusButton(const Vector2 &pos_, std::string label_, int &i);
	void update();
	void draw();
};

//doubleへの参照を取り、バーのスライドで値を更新する
class SlideBar : public IButton
{
public:
	SlideBar(const Vector2 &pos_, std::string label_, double &val, double minVal_, double maxVal_);

	class Bar{
	public:
		Bar(const Vector2 &pos_, Vector2 size_);
		Vector2 pos;
		Vector2 size;
		DWORD color;
		double boxAlpha;
		void draw();
	};

	int marge;
	Vector2 col_size;
	Bar bar;
	double mouse_pos_x;
	double &ref_val;
	double minVal;
	double maxVal;

	void checkMouse();
	void update();
	void draw();
};

//intへの参照をとり、バーのスライドで値を更新する
class SlideBarInt : public IButton
{
public:
	SlideBarInt(const Vector2 &pos_, std::string label_, int &ref_i_, int minVal_, int maxVal_);

	class Bar{
	public:
		Bar(const Vector2 &pos_, Vector2 size_);
		Vector2 pos;
		Vector2 size;
		DWORD color;
		double boxAlpha;
		void draw();
	};

	int marge;
	Vector2 col_size;
	Bar bar;
	double mouse_pos_x;
	double mouse_x_rate; // 0~1.0 or -1~1
	int &ref_i;
	int minVal;
	int maxVal;

	void checkMouse();
	void update();
	void draw();
};

//ブールを取り、それをtrue, falseに書き換えるボタン
class BoolButton : public IButton
{
public:
	bool &flag;//ボタンに登録されるブール値
	BoolButton(const Vector2 &pos_, Vector2 size_, std::string label_, bool &flag_);
	void update();
	void draw();
};

//複数のボタンを要素に持ち、それを移動する
class ButtonKeeper : public IButton
{
public:
	ButtonKeeper(const Vector2 &pos_, Vector2 size_, std::string label_);

	int marge_y;
	Vector2 elementSize;
	std::vector<std::shared_ptr<IButton>> button_vec;
	void add(std::shared_ptr<IButton> ptr);

	void setElementColor();
	void update();
	void draw();
};

/*
例：
ButtonAdder::addDValIntButton("strNum", 1, 10);
これで右下に MIN1, MAX10のstrNumボタンが追加される
*/
class ButtonAdder{
public:
	static Vector2 pos;
	static Vector2 vel;
	static Vector2 size;
	ButtonAdder();
	static void add(std::shared_ptr<IButton> ptr);
	static void addDValIntButton(const std::string &valName, int min, int max);
	static void addDValDoubleButton(const std::string &valName, double min, double max);
	static void addDValBoolButton(const std::string &valName);
};