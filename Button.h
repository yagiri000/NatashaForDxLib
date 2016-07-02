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



//�F��\���N���X(hue = 0~360)
struct HSV360
{
	HSV360(double, double, double);
	void set(double, double, double);
	DWORD GetRGB();
	double h;
	double s;
	double v;
};

//�{�^���N���X�Q�̊��N���X
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
	bool isClickEnd;//�}�E�X�������ꂽ
	bool isPushing;

	IButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_);

	virtual void checkMouse();
	virtual void moveColor();
	virtual void die();
	virtual void update() = 0;
	virtual void draw();
};

//�������\������i�@�\�Ȃ��j
class Label : public IButton
{
public:
	Label(const Vector2 &pos_, Vector2 size_, std::string label_);
	void update();
};

//�{�^���������ꂽ���A�w�肳�ꂽ���������s����
class ClickButton : public IButton
{
public:
	ClickButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_);
	void update();
	void draw();
};

//�{�^����������Ă���ԁA�w�肳�ꂽ���������s����
class ClickingButton : public IButton
{
public:
	ClickingButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_);
	void moveColor();
	void update();
	void draw();
};

//�{�^����On�̊Ԏw�肳�ꂽ���������s����
class OnOffButton : public IButton
{
public:
	bool isOn;//�{�^�����I�����ǂ���
	OnOffButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_);
	void update();
	void draw();
};

//int�ւ̎Q�Ƃ��Ƃ�A�{�^���N���b�N�Œl���X�V����
class PlusMinusButton : public IButton
{
public:
	std::vector<std::shared_ptr<ClickButton>> click_vec;
	int &target;
	PlusMinusButton(const Vector2 &pos_, std::string label_, int &i);
	void update();
	void draw();
};

//double�ւ̎Q�Ƃ����A�o�[�̃X���C�h�Œl���X�V����
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

//int�ւ̎Q�Ƃ��Ƃ�A�o�[�̃X���C�h�Œl���X�V����
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

//�u�[�������A�����true, false�ɏ���������{�^��
class BoolButton : public IButton
{
public:
	bool &flag;//�{�^���ɓo�^�����u�[���l
	BoolButton(const Vector2 &pos_, Vector2 size_, std::string label_, bool &flag_);
	void update();
	void draw();
};

//�����̃{�^����v�f�Ɏ����A������ړ�����
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
��F
ButtonAdder::addDValIntButton("strNum", 1, 10);
����ŉE���� MIN1, MAX10��strNum�{�^�����ǉ������
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