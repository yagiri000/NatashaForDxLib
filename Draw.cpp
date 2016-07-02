//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once

#include <DxLib.h>
#include "Draw.h"
#include <string>


DrawImpl Draw;
DrawImpl DrawAbs;

DrawImpl::DrawImpl() :
dx(0),
dy(0),
shiftVec(0, 0)
{
}


void DrawImpl::setdxdy(int x, int y){
	dx = x;
	dy = y;
	shiftVec.Set(x, y);
}

//Vector2�g�p

//�ʏ�̕`��E���W�͍�����w��
void DrawImpl::normal(const Vector2& pos, int GrHandle, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawGraph(pos.x + dx, pos.y + dy, GrHandle, 1);
}

//�摜�̒����̍��W���w�肵�ĕ`��
void DrawImpl::center(const Vector2& pos, int GrHandle, int alpha, int TurnFlag, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawRotaGraph(pos.x + dx, pos.y + dy, 1.0, 0.0, GrHandle, 1, TurnFlag);
}

//�g��E��]�`��
void DrawImpl::exrot(const Vector2& pos, double ExtRate, double Angle, int GrHandle, int alpha, int TurnFlag, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawRotaGraph(pos.x + dx, pos.y + dy, ExtRate, Angle, GrHandle, 1, TurnFlag);
}

//�g��E��]�E�����w��`��
void DrawImpl::exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double Angle, int GrHandle, int alpha, int TurnFlag, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawRotaGraph3(pos.x + dx, pos.y + dy, center_pos.x, center_pos.y, Exrate_vec.x, Exrate_vec.y, Angle, GrHandle, 1, TurnFlag);
}

//3������]�`��
void DrawImpl::rot3D(const Vector2& pos, const Vector2& exRate, float zRot, float xRot, float yRot, int gHandle, int turnFlag){
	MATRIX m;
	int w, h;
	GetGraphSize(gHandle, &w, &h);
	w = (int)(w*exRate.x);
	h = (int)(h*exRate.y);
	if (turnFlag == TRUE)
		w *= -1;
	VECTOR v[4] = { VGet(-(float)w / 2, -(float)h / 2, 0), VGet((float)w / 2, -(float)h / 2, 0)
		, VGet(-(float)w / 2, (float)h / 2, 0), VGet((float)w / 2, (float)h / 2, 0) };

	m = MGetRotZ(zRot);
	for (int i = 0; i < 4; i++)
		v[i] = VTransform(v[i], m);
	if (xRot != 0.0f)
	{
		m = MGetRotX(xRot);
		for (int i = 0; i < 4; i++)
			v[i] = VTransform(v[i], m);
	}
	if (yRot != 0.0f)
	{
		m = MGetRotY(yRot);
		for (int i = 0; i < 4; i++)
			v[i] = VTransform(v[i], m);
	}

	DrawModiGraphF(pos.x + v[0].x, pos.y + v[0].y, pos.x + v[1].x, pos.y + v[1].y, pos.x + v[3].x, pos.y + v[3].y, pos.x + v[2].x, pos.y + v[2].y, gHandle, TRUE);
}
//���R�ό`�`��
void DrawImpl::modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int GrHandle, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawModiGraph(
		pos1.x + dx, pos1.y + dy, pos2.x + dx, pos2.y + dy,
		pos3.x + dx, pos3.y + dy, pos4.x + dx, pos4.y + dy,
		GrHandle, 1);
}

//����E�E�����w�肵�ĕ`��
void DrawImpl::modi2(const Vector2& pos1, const Vector2& pos2, int GrHandle, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawExtendGraph(pos1.x + dx, pos1.y + dy, pos2.x + dx, pos2.y + dy, GrHandle, 1);
}

//�ȉ~��ɃO���t��`��@r�ŉ~�̔��a�Erate:�c��r��rate�̔�̕��Ђ��Ⴐ������Eangle:��]�p
void DrawImpl::modiOval(const Vector2& pos, double r, double rate, double angle, int GrHandle, int alpha, int blendMode){
	float gx[4];
	float gy[4];
	float dr = PI * -0.75;
	for (int i = 0; i < 4; i++){
		float dangle = PI * 0.5;
		gx[i] = pos.x + r * cos(angle + i * dangle - dr);
		gy[i] = pos.y + rate * r * sin(angle + i * dangle - dr);
	}

	SetDrawBlendMode(blendMode, alpha);
	DrawModiGraphF(
		gx[0] + dx, gy[0] + dy,
		gx[1] + dx, gy[1] + dy,
		gx[2] + dx, gy[2] + dy,
		gx[3] + dx, gy[3] + dy, GrHandle, 1);
}

//�摜�̎w�肵�������̂ݕ`��@�`����W�E������W�E�`��摜�T�C�Y
void DrawImpl::trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int GrHandle, int alpha, int TurnFlag, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawRectGraph(pos.x + dx, pos.y + dy, graph_ul_pos.x, graph_ul_pos.y, size.x, size.y, GrHandle, 1, TurnFlag);
}

//�T�[�N���Q�[�W�`��@(dx, dy)���V�t�g
void DrawImpl::circleGauge(const Vector2& pos, double percent, int GrHandle, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawCircleGauge(pos.x + dx, pos.y + dy, 100, GrHandle, 100 - percent);
}

//�T�[�N���Q�[�W�`��i�t�����j�@(dx, dy)���V�t�g
void DrawImpl::circleGaugeReverse(const Vector2& pos, double percent, int GrHandle, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawCircleGauge(pos.x + dx, pos.y + dy, percent, GrHandle);
}

//�}�`�`��֐�

//����`��
void DrawImpl::line(const Vector2& start_pos, const Vector2& end_pos, int color, int alpha, int Thickness, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawLine(start_pos.x + dx, start_pos.y + dy, end_pos.x + dx, end_pos.y + dy, color, Thickness);
}

//�Ǝ�
//�n�_�ƏI�_�ւ̋����A�p�x���w�肵�Đ���`��
void DrawImpl::lineAngle(const Vector2& start_pos, int r, double angle, int color, int alpha, int Thickness, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawLine(start_pos.x + dx, start_pos.y + dy, start_pos.x + r * cos(angle) + dx, start_pos.y + r * sin(angle) + dy, color, Thickness);
}

//����`��
void DrawImpl::box(const Vector2& pos1, const Vector2& pos2, int color, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawBox(pos1.x + dx, pos1.y + dy, pos2.x + dx, pos2.y + dy, color, 1);
}

//�Ǝ�
//���S���w�肵�Ĕ���`��
void DrawImpl::centerBox(const Vector2& center_pos, const Vector2& size, int color, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawBox(
		center_pos.x - size.x / 2 + dx, center_pos.y - size.y / 2 + dy,
		center_pos.x + size.x / 2 + dx, center_pos.y + size.y / 2 + dy,
		color, 1);
}

//�~��`��
void DrawImpl::circle(const Vector2& pos, int r, int color, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawCircle(pos.x + dx, pos.y + dy, r, color, 1);
}

//�~��`��
void DrawImpl::circleRing(const Vector2& pos, int r, int ringWidth, int color, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawCircle(pos.x + dx, pos.y + dy, r, color, 0, ringWidth);
}

//�O�p�`��`��
void DrawImpl::triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawTriangle(pos1.x + dx, pos1.y + dy, pos2.x + dx, pos2.y + dy, pos3.x + dx, pos3.y + dy, color, 1);
}


//�����`��֐�
void DrawImpl::TextDrawLog::set(const Vector2 &pos_, int color_, int fontHandle_, int alpha_, int blendMode_){
	pos = pos_;
	color = color_;
	fontHandle = fontHandle_;
	alpha = alpha_;
	blendMode = blendMode_;
}

//������`��
void DrawImpl::text(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	DrawFormatStringToHandle(pos.x + dx, pos.y + dy, color, fontHandle, "%s", str.c_str());
	textDrawLog.set(pos, color, fontHandle, alpha, blendMode);
}

//������`��
void DrawImpl::normalText(const Vector2& pos, const std::string &str){
	text(pos, 0x888888, textDrawLog.fontHandle, str, 255);
}

//������`��
void DrawImpl::normalTextBox(const Vector2& pos, const std::string &str){
	textBox(pos, 0xFFFFFF, textDrawLog.fontHandle, str, 255, HorizontalPlace::left, VerticalPlace::top, Vector2(8, 8), 0x000000, 128);
}

//������`��E�ʒu�w��
void DrawImpl::textPlace(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh, VerticalPlace::en fv, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	Vector2 dPos(0, 0);
	if (fh == HorizontalPlace::en::center){
		dPos.x -= GetDrawFormatStringWidthToHandle(fontHandle, "%s", str.c_str()) / 2.0;
	}
	else if (fh == HorizontalPlace::en::right){
		dPos.x -= GetDrawFormatStringWidthToHandle(fontHandle, "%s", str.c_str());
	}
	if (fv == VerticalPlace::en::center){
		dPos.y -= GetFontSizeToHandle(fontHandle) / 2.0;
	}
	else if (fv == VerticalPlace::en::bottom){
		dPos.y -= GetFontSizeToHandle(fontHandle);
	}
	DrawFormatStringToHandle(pos.x + dx + dPos.x, pos.y + dy + dPos.y, color, fontHandle, "%s", str.c_str());
	textDrawLog.set(pos, color, fontHandle, alpha, blendMode);
}

//������`��E�ʒu�w��
void DrawImpl::textPlaceSpace(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, double space, HorizontalPlace::en fh, VerticalPlace::en fv, int blendMode){
	Vector2 dPos(0, 0);
	if (fv == VerticalPlace::en::center){
		dPos.y -= GetFontSizeToHandle(fontHandle) / 2.0;
	}
	else if (fv == VerticalPlace::en::bottom){
		dPos.y -= GetFontSizeToHandle(fontHandle);
	}

	SetDrawBlendMode(blendMode, alpha);
	if (fh == HorizontalPlace::en::left){
		for (int i = 0; i < str.size(); i++){
			centerText(Vector2(pos.x + i * space, pos.y) + dPos, color, fontHandle, str.substr(i, 1), alpha, blendMode);
		}
	}
	else if (fh == HorizontalPlace::en::center){
		if ((str.size() % 2) == 0){
			for (int i = 0; i < str.size(); i++){
				dPos.x = -(double)(str.size() / 2) * space + space / 2;
				centerText(Vector2(pos.x + i * space, pos.y) + dPos, color, fontHandle, str.substr(i, 1), alpha, blendMode);
			}
		}
		else{
			for (int i = 0; i < str.size(); i++){
				dPos.x = -(double)(str.size() / 2) * space;
				centerText(Vector2(pos.x + i * space, pos.y) + dPos, color, fontHandle, str.substr(i, 1), alpha, blendMode);
			}
		}
	}
	else if (fh == HorizontalPlace::en::right){
		for (int i = 0; i < str.size(); i++){
			dPos.x = -(double)(str.size() - 1) * space;
			centerText(Vector2(pos.x + i * space, pos.y) + dPos, color, fontHandle, str.substr(i, 1), alpha, blendMode);
		}
	}
	textDrawLog.set(pos, color, fontHandle, alpha, blendMode);
}

//�e�L�X�g�Ƃ��̔w�i��
void DrawImpl::textBox(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh, VerticalPlace::en fv, const Vector2 &boxMargeV2, int boxColor, int boxAlpha, int blendMode, int boxBlendMode){
	Vector2 dPos(0, 0);
	Vector2 fontSize = Vector2(
		GetDrawFormatStringWidthToHandle(fontHandle, "%s", str.c_str()),
		GetFontSizeToHandle(fontHandle)
		);
	if (fh == HorizontalPlace::en::center){
		dPos.x -= fontSize.x / 2.0;
	}
	else if (fh == HorizontalPlace::en::right){
		dPos.x -= fontSize.x;
	}
	if (fv == VerticalPlace::en::center){
		dPos.y -= fontSize.y / 2.0;
	}
	else if (fv == VerticalPlace::en::bottom){
		dPos.y -= fontSize.y;
	}
	Vector2 shift(-(int)fh * fontSize.x * 0.5, -(int)fv * fontSize.y * 0.5);
	Vector2 leftTop(pos.x + dx + dPos.x, pos.y + dy + dPos.y);
	Draw.box(leftTop - boxMargeV2 * 0.5, leftTop + fontSize + boxMargeV2 * 0.5, boxColor, boxAlpha);
	SetDrawBlendMode(blendMode, alpha);
	DrawFormatStringToHandle(leftTop.x, leftTop.y, color, fontHandle, "%s", str.c_str());
	textDrawLog.set(leftTop, color, fontHandle, alpha, blendMode);
}

//������`��
void DrawImpl::textNextLine(const std::string &str){
	auto r = textDrawLog;
	r.pos.y += r.yDif;
	text(r.pos, r.color, r.fontHandle, str, r.alpha, r.blendMode);
}

//������`��
void DrawImpl::textLine(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, HorizontalPlace::en fh, VerticalPlace::en fv, int blendMode){
	Vector2 dPos(0, 0);
	if (fh == HorizontalPlace::en::center){
		dPos.x -= GetDrawFormatStringWidthToHandle(fontHandle, "%s", str.c_str()) / 2.0;
	}
	else if (fh == HorizontalPlace::en::right){
		dPos.x -= GetDrawFormatStringWidthToHandle(fontHandle, "%s", str.c_str());
	}
	if (fv == VerticalPlace::en::center){
		dPos.y -= GetFontSizeToHandle(fontHandle) / 2.0;
	}
	else if (fv == VerticalPlace::en::bottom){
		dPos.y -= GetFontSizeToHandle(fontHandle);
	}

	SetDrawBlendMode(blendMode, alpha);

	size_t preNum = 0;
	size_t num = 0;
	while (1){
		preNum = num;
		num = str.find('\n', num);
		DrawFormatStringToHandle(pos.x + dx + dPos.x, pos.y + dy + dPos.y, color, fontHandle, "%s", str.substr(preNum, num - preNum).c_str());
		if (num == std::string::npos){
			break;
		}
		else{
			dPos += Vector2(0, GetFontSizeToHandle(fontHandle));
			num++;
		}
	}
	textDrawLog.set(pos, color, fontHandle, alpha, blendMode);
}

//�w�肵�����W�𒆐S�ɕ�����`��
void DrawImpl::centerText(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	int wd = GetDrawFormatStringWidthToHandle(fontHandle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x + dx - wd / 2, pos.y + dy, color, fontHandle, "%s", str.c_str());
}

//�����̉E��̍��W���w�肵�ĕ�����`��
void DrawImpl::rightText(const Vector2& pos, int color, int fontHandle, const std::string &str, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	int wd = GetDrawFormatStringWidthToHandle(fontHandle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x + dx - wd, pos.y + dy, color, fontHandle, "%s", str.c_str());
}

//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
void DrawImpl::textSpace(const Vector2& pos, int color, int fontHandle, int space, const std::string &str, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	for (int i = 0; i < str.size(); i++){
		centerText(Vector2(pos.x + i * space, pos.y), color, fontHandle, str.substr(i, 1), alpha, blendMode);
	}
}

//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
void DrawImpl::centerTextSpace(const Vector2& pos, int color, int fontHandle, int space, const std::string &str, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	if ((str.size() % 2) == 0){
		for (int i = 0; i < str.size(); i++){
			double basex = -(double)(str.size() / 2) * space + space / 2;
			centerText(Vector2(pos.x + i * space + basex, pos.y), color, fontHandle, str.substr(i, 1), alpha, blendMode);
		}
	}
	else{
		for (int i = 0; i < str.size(); i++){
			double basex = -(double)(str.size() / 2) * space;
			centerText(Vector2(pos.x + i * space + basex, pos.y), color, fontHandle, str.substr(i, 1), alpha, blendMode);
		}
	}
}
//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
void DrawImpl::rightTextSpace(const Vector2& pos, int color, int fontHandle, int space, const std::string &str, int alpha, int blendMode){
	SetDrawBlendMode(blendMode, alpha);
	for (int i = 0; i < str.size(); i++){
		double basex = -(double)(str.size()) * space;
		centerText(Vector2(pos.x + i * space + basex, pos.y), color, fontHandle, str.substr(i, 1), alpha, blendMode);
	}
}
