//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once
#include <iostream>
#include "Vector2.h"

const Vector2 Vector2::zero(0, 0);
const Vector2 Vector2::one(1, 1);
const Vector2 Vector2::right(1, 0);
const Vector2 Vector2::left(-1, 0);
const Vector2 Vector2::up(0, -1);
const Vector2 Vector2::down(0, 1);

//2次元上の点を表すクラス
//コンストラクタ定義
Vector2::Vector2() :
x(0), y(0)
{
}


Vector2::Vector2(double x_, double y_) : 
x(x_), y(y_)
{
}

//オペレーターオーバーロード
Vector2& Vector2::operator +=(const Vector2& t){
	x += t.x;
	y += t.y;
	return *this;
}
Vector2& Vector2::operator -=(const Vector2& t){
	x -= t.x;
	y -= t.y;
	return *this;
}
Vector2 Vector2::operator +(const Vector2& t) const{
	Vector2 temp;
	temp.x = x + t.x;
	temp.y = y + t.y;
	return temp;
}
Vector2 Vector2::operator -(const Vector2& t) const{
	Vector2 temp;
	temp.x = x - t.x;
	temp.y = y - t.y;
	return temp;
}
Vector2& Vector2::operator *=(double t){
	x *= t;
	y *= t;
	return *this;
}
Vector2& Vector2::operator /=(double t){
	x /= t;
	y /= t;
	return *this;
}
Vector2 Vector2::operator *(double t) const{
	Vector2 temp;
	temp.x = x * t;
	temp.y = y * t;
	return temp;
}
Vector2 Vector2::operator /(double t) const{
	Vector2 temp;
	temp.x = x / t;
	temp.y = y / t;
	return temp;
}

//内積
double Vector2::operator *(const Vector2& t){
	return x * t.x + y * t.y;
}

//外積
double Vector2::cross(const Vector2& t){
	return x * t.y - y * t.x;
}

//操作関数
void Vector2::Set(double x_, double y_)
{
	x = x_;
	y = y_;
}

//原点を中心に回転
void Vector2::Rotate(double rad)
{
	double sint = sin(rad), cost = cos(rad);	//sinとcosの値
	double tx = x;	//一時格納
	x = cost * tx - sint * y;		// ( cosθ -sinθ) ( x )
	y = sint * tx + cost * y;		// ( sinθ xosθ ) ( y )
}

//centerを中心に回転
void Vector2::RotateOnPoint(double rad, const Vector2 &center)
{
	double sint = sin(rad), cost = cos(rad);	//sinとcosの値
	double tx = x - center.x;	//一時格納
	double ty = y - center.y;	//一時格納
	x = cost * tx - sint * ty + center.x;		// ( cosθ -sinθ) ( x )
	y = sint * tx + cost * ty + center.y;		// ( sinθ xosθ ) ( y )
}

//原点を中心にベクトルを回転したものを返す
Vector2 Vector2::GetRotate(double rad){
	Vector2 temp = *this;
	double sint = sin(rad), cost = cos(rad);	//sinとcosの値
	double tx = temp.x;	//一時格納
	temp.x = cost * tx - sint * temp.y;		// ( cosθ -sinθ) ( x )
	temp.y = sint * tx + cost * temp.y;		// ( sinθ xosθ ) ( y )
	return temp;
}

//centerを中心に回転したベクトルを返す
Vector2 Vector2::GetRotateOnPoint(double rad, const Vector2 &center){
	Vector2 temp = *this;
	double sint = sin(rad), cost = cos(rad);	//sinとcosの値
	double tx = temp.x - center.x;	//一時格納
	double ty = temp.y - center.y;	//一時格納
	temp.x = cost * tx - sint * ty + center.x;		// ( cosθ -sinθ) ( x )
	temp.y = sint * tx + cost * ty + center.y;		// ( sinθ xosθ ) ( y )
	return temp;
}

//dx,dy分だけ移動
void Vector2::Translate(double dx, double dy)
{
	x += dx;
	y += dy;
}

//ベクトルの大きさを返す
double Vector2::GetMagnitude(){
	return sqrt(x*x + y*y);
}

//ベクトルの大きさを返す
double Vector2::GetSqrMagnitude(){
	return x*x + y*y;
}

//ベクトルを正規化する
void Vector2::Normalize(){
	double r = sqrt(x*x + y*y);
	if (r < 0.01){
		r = 0.01;
	}
	x /= r;
	y /= r;
}

//正規化されたベクトルを返す
Vector2 Vector2::GetNormalized(){
	Vector2 temp = *this;
	double r = sqrt(x*x + y*y);
	if (r < 0.001){
		r = 0.001;
	}
	temp.x /= r;
	temp.y /= r;
	return temp;
}

//ベクトルの角度を返す
double Vector2::GetAngle(){
	return atan2(y, x);
}

//極座標系式で表されたベクトルを返す static
Vector2 Vector2::GetPolar(double r, double angle){
	Vector2 temp;
	temp.x = r * cos(angle);
	temp.y = r * sin(angle);
	return temp;
}



