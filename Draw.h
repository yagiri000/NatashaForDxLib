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

//�V���O���g��Draw�N���X
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

	//�`�悷����W�̃V�t�g�ʂ�ݒ�
	void setdxdy(int x, int y);

	//�摜�̍���̍��W���w�肵�ĕ`��
	void normal(const Vector2& pos, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�摜�̒����̍��W���w�肵�ĕ`��
	void center(const Vector2& pos, int gHandle, int alpha, int turnFlag = 0, int blendMode = DX_BLENDMODE_ALPHA);

	//�g��E��]�`��
	void exrot(const Vector2& pos, double ExtRate, double angle, int gHandle, int alpha, int turnFlag = 0, int blendMode = DX_BLENDMODE_ALPHA);

	//�g��E��]�E�����w��`��
	void exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double angle, int gHandle, int alpha, int turnFlag = 0, int blendMode = DX_BLENDMODE_ALPHA);
	
	//3������]�`��
	void rot3D(const Vector2& pos, const Vector2& exRate, float zRot, float xRot, float yRot, int gHandle, int turnFlag = 0);

	//���R�ό`�`��
	void modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//����E�E�����w�肵�ĕ`��
	void modi2(const Vector2& pos1, const Vector2& pos2, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�ȉ~��ɃO���t��`��@r�ŉ~�̔��a�Erate:�c��r��rate�̔�̕��Ђ��Ⴐ������Eangle:��]�p
	void modiOval(const Vector2& pos, double r, double rate, double angle, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�摜�̎w�肵�������̂ݕ`��@�`����W�E������W�E�`��摜�T�C�Y
	void trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int gHandle, int alpha, int turnFlag = 0, int blendMode = DX_BLENDMODE_ALPHA);

	//�T�[�N���Q�[�W�`��@(dx, dy)���V�t�g
	void circleGauge(const Vector2& pos, double percent, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�T�[�N���Q�[�W�`��i�t�����j�@(dx, dy)���V�t�g
	void circleGaugeReverse(const Vector2& pos, double percent, int gHandle, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�}�`�`��֐�
	//����`��
	void line(const Vector2& start_pos, const Vector2& end_pos, int color, int alpha, int thickness = 1, int blendMode = DX_BLENDMODE_ALPHA);

	//�n�_�ƏI�_�ւ̋����A�p�x���w�肵�Đ���`��
	void lineAngle(const Vector2& start_pos, int r, double angle, int color, int alpha, int thickness = 1, int blendMode = DX_BLENDMODE_ALPHA);

	//����`��
	void box(const Vector2& pos1, const Vector2& pos2, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//���S���w�肵�Ĕ���`��
	void centerBox(const Vector2& center_pos, const Vector2& size, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�~��`��
	void circle(const Vector2& pos, int r, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�~��`��
	void circleRing(const Vector2& pos, int r, int ringWidth, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�O�p�`��`��
	void triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�����`��֐�
	void text(const Vector2& pos, int color, int fonthandle, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�����`��֐�
	void normalText(const Vector2& pos, const std::string &str);

	//�����`��֐�
	void normalTextBox(const Vector2& pos, const std::string &str);

	//������`��
	void textPlace(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh = HorizontalPlace::left, VerticalPlace::en fv = VerticalPlace::top, int blendMode = DX_BLENDMODE_ALPHA);

	//������`��E�ʒu�w��
	void textPlaceSpace(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, double space, HorizontalPlace::en fh = HorizontalPlace::left, VerticalPlace::en fv = VerticalPlace::top, int blendMode = DX_BLENDMODE_ALPHA);

	//������`��E�����̔w�i�ɔ���`��
	void textBox(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh, VerticalPlace::en fv, const Vector2 &boxMargeV2, int boxColor, int boxAlpha, int blendMode = DX_BLENDMODE_ALPHA, int boxBlendMode = DX_BLENDMODE_ALPHA);

	//�O�񏑂��������̎��̍s�ɕ�����`��
	void textNextLine(const std::string &str);

	//�����s�ɕ�����`��E"\n"�ŉ��s
	void textLine(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh = HorizontalPlace::left, VerticalPlace::en fv = VerticalPlace::top, int blendMode = DX_BLENDMODE_ALPHA);

	//�w�肵�����W�𒆐S�ɕ�����`��
	void centerText(const Vector2& pos, int color, int fonthandle, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�����̉E��̍��W���w�肵�ĕ�����`��
	void rightText(const Vector2& pos, int color, int fonthandle, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
	void textSpace(const Vector2& pos, int color, int fonthandle, int space, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);
	
	//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
	void centerTextSpace(const Vector2& pos, int color, int fonthandle, int space, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

	//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
	void rightTextSpace(const Vector2& pos, int color, int fonthandle, int space, const std::string &str, int alpha, int blendMode = DX_BLENDMODE_ALPHA);

};


extern DrawImpl Draw;
extern DrawImpl DrawAbs;