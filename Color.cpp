#include "Color.h"
#include <iostream>
#include <algorithm>

const int Color::White	= 0xFFFFFF;
const int Color::Black	= 0x000000;
const int Color::Gray	= 0x888888;
const int Color::Red	= 0xFF0000;
const int Color::Orange	= 0xFF8800;
const int Color::Yellow	= 0xFFFF00;
const int Color::Green	= 0x00FF00;
const int Color::Cyan	= 0x00FFFF;
const int Color::DBlue	= 0x0088FF;
const int Color::Blue	= 0x0000FF;
const int Color::Purple	= 0xFF00FF;


Color::Color()
{
}


Color::~Color()
{
}

HSV::HSV(size_t color_)
{
	double max;
	double min;
	double R, G, B;

	// 0.0 - 1.0（255分率）
	R = (double)(color_ >> 16 & 0xFF) / 255.0;
	G = (double)(color_ >> 8 & 0xFF) / 255.0;
	B = (double)(color_ >> 0 & 0xFF) / 255.0;

	// 最大値・最小値
	if (R >= G && R >= B) {
		max = R;
		min = (G < B) ? G : B;
	}
	else if (G >= R && G >= B) {
		max = G;
		min = (R < B) ? R : B;
	}
	else {
		max = B;
		min = (R < G) ? R : G;
	}


	if (abs(max - min) < 0.001){
		h = 0.0;
	}
	else{
		if (max == R) {
			h = 60 * (G - B) / (max - min);
		}
		else if (max == G){
			h = 60 * (B - R) / (max - min) + 120;
		}
		else {
			h = 60 * (R - G) / (max - min) + 240;
		}
		if (h < 0.0) {
			h += 360.0;
		}
	}
	// Hue（色相）

	h /= 360.0;

	// Saturation（彩度）
	s = (max - min) / max;
	// Value（明度）
	v = max;
}

HSV::HSV() :
h(0),
s(0),
v(0)
{
}

HSV::HSV(double h_, double s_, double v_) :
h(h_),
s(s_),
v(v_)
{
}

int HSV::operator()(){
	return getColor();
}

int HSV::getColor(){
	float f;
	int i, p, q, t;
	int rgb[3];

	double tmpH = fmod(h, 1.0);
	if (tmpH < 0.0){
		tmpH += 1.0;
	}
	i = ((int)floor(tmpH * 6.0f)) % 6;
	f = (float)(h * 6.0f) - (float)floor(h * 6.0f);
	p = (int)(255.0f * v * (1.0f - (s)));
	q = (int)(255.0f * v * (1.0f - (s)* f));
	t = (int)(255.0f * v * (1.0f - (s)* (1.0f - f)));

	switch (i){
	case 0: rgb[0] = 255.0f * v; rgb[1] = t; rgb[2] = p; break;
	case 1: rgb[0] = q; rgb[1] = 255.0f * v; rgb[2] = p; break;
	case 2: rgb[0] = p; rgb[1] = 255.0f * v; rgb[2] = t; break;
	case 3: rgb[0] = p; rgb[1] = q; rgb[2] = 255.0f * v; break;
	case 4: rgb[0] = t; rgb[1] = p; rgb[2] = 255.0f * v; break;
	case 5: rgb[0] = 255.0f * v; rgb[1] = p; rgb[2] = q; break;
	}

	return ((rgb[0]) << 16) + ((rgb[1]) << 8) + rgb[2];
}

void HSV::set(double h_, double s_, double v_){
	h = h_;
	s = s_;
	v = v_;
}

HSV HSV::operator*(double rate) const{
	HSV c(*this);
	c.h *= rate;
	c.s *= rate;
	c.v *= rate;
	return c;
}

HSV HSV::operator+(const HSV &a) const{
	HSV c(*this);
	c.h += a.h;
	c.s += a.s;
	c.v += a.v;
	return c;
}


