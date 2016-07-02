//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------

#pragma once

//2次元上の点を表すクラス
class Vector2
{
public:
	double x;
	double y;

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 right;
	static const Vector2 left;
	static const Vector2 up;
	static const Vector2 down;

	//コンストラクタ定義
	Vector2();
	Vector2(double x_, double y_);

	//オペレーターオーバーロード
	Vector2& operator +=(const Vector2& t);
	Vector2& operator -=(const Vector2& t);
	Vector2 operator +(const Vector2& t) const;
	Vector2 operator -(const Vector2& t) const;
	Vector2& operator *=(double t);
	Vector2& operator /=(double t);
	Vector2 operator *(double t) const;
	Vector2 operator /(double t) const;

	//内積
	double operator *(const Vector2& t);

	//外積
	double cross(const Vector2& t);

	//操作関数
	void Set(double x_, double y_);

	//原点を中心に回転
	void Rotate(double rad);

	//centerを中心に回転
	void RotateOnPoint(double rad, const Vector2 &center);

	//原点を中心にベクトルを回転したものを返す
	Vector2 GetRotate(double rad);

	//centerを中心に回転したベクトルを返す
	Vector2 GetRotateOnPoint(double rad, const Vector2 &center);

	//dx,dy分だけ移動
	void Translate(double dx, double dy);

	//ベクトルの大きさを返す
	double GetMagnitude();

	//ベクトルの大きさを返す
	double GetSqrMagnitude();

	//ベクトルを正規化する
	void Normalize();

	//正規化されたベクトルを返す
	Vector2 GetNormalized();

	//ベクトルの角度を返す
	double GetAngle();

	//極座標系式で表されたベクトルを返す static
	static Vector2 GetPolar(double r, double angle);
};