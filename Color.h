//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once
class Color
{
public:
	static const int White;
	static const int Black;
	static const int Gray;
	static const int Red;
	static const int Orange;
	static const int Yellow;
	static const int Green;
	static const int Cyan;
	static const int DBlue;
	static const int Blue;
	static const int Purple;

	Color();
	~Color();
};

class HSV{
public:
	double h;
	double s;
	double v;
	HSV();
	HSV(size_t color_);
	HSV(double h_, double s_, double v_);
	int operator()();
	int getColor();
	void set(double h_, double s_, double v_);
	HSV operator*(double rate) const;
	HSV operator+(const HSV &a) const;
};

using C = Color;
