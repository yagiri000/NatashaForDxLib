//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------

#pragma once

//2������̓_��\���N���X
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

	//�R���X�g���N�^��`
	Vector2();
	Vector2(double x_, double y_);

	//�I�y���[�^�[�I�[�o�[���[�h
	Vector2& operator +=(const Vector2& t);
	Vector2& operator -=(const Vector2& t);
	Vector2 operator +(const Vector2& t) const;
	Vector2 operator -(const Vector2& t) const;
	Vector2& operator *=(double t);
	Vector2& operator /=(double t);
	Vector2 operator *(double t) const;
	Vector2 operator /(double t) const;

	//����
	double operator *(const Vector2& t);

	//�O��
	double cross(const Vector2& t);

	//����֐�
	void Set(double x_, double y_);

	//���_�𒆐S�ɉ�]
	void Rotate(double rad);

	//center�𒆐S�ɉ�]
	void RotateOnPoint(double rad, const Vector2 &center);

	//���_�𒆐S�Ƀx�N�g������]�������̂�Ԃ�
	Vector2 GetRotate(double rad);

	//center�𒆐S�ɉ�]�����x�N�g����Ԃ�
	Vector2 GetRotateOnPoint(double rad, const Vector2 &center);

	//dx,dy�������ړ�
	void Translate(double dx, double dy);

	//�x�N�g���̑傫����Ԃ�
	double GetMagnitude();

	//�x�N�g���̑傫����Ԃ�
	double GetSqrMagnitude();

	//�x�N�g���𐳋K������
	void Normalize();

	//���K�����ꂽ�x�N�g����Ԃ�
	Vector2 GetNormalized();

	//�x�N�g���̊p�x��Ԃ�
	double GetAngle();

	//�ɍ��W�n���ŕ\���ꂽ�x�N�g����Ԃ� static
	static Vector2 GetPolar(double r, double angle);
};