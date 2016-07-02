//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "myglobal.h"
#include "Resource.h"
#include "Vector2.h"
#include "Color.h"
#include "Draw.h"

//2015/01/04 �X�V

/*
class Input
class Random

namespace Func
	-�����蔻��
	-�x�N�g��
	-�C�[�W���O�Ȑ�
	-�֗��֐�
*/



static const int LMOUSE = 250;
static const int RMOUSE = 251;

//!!!!!!!!!!!!! ���� !!!!!!!!!!!!!
//get����O��static�����o�ɃA�N�Z�X����͕̂s�\
//�}�E�X���W�E�L�[��ԁE�N������̃t���[������ێ�����N���X
class Input{
public:

	Input();

	Input& operator=(const Input& a) = delete;
	Input(const Input& a) = delete;

	static Input& get();

	static void update();

	//�L�[��������Ă��邩��bool�ŕԂ�
	static bool keyNow(int i);

	//�L�[�������ꂽ�t���[������true��Ԃ�
	static bool keyDown(int i);

	//�L�[�������ꂽ�t���[������true��Ԃ�
	static bool keyUp(int i);

	//�L�[��������Ă���t���[����Ԃ�
	static int keyFrame(int i);

	static int mousex();

	static int mousey();

	static Vector2 mousePos();

	static int eFrame();

	//Allzeroframe�̊�keystate�����ׂ�0��
	static void setAllZeroFrame(int t);

	//Allzerooff���Ă΂��܂�keystate�����ׂ�0��
	static void allZeroOn();

	//keystate���ׂ�0 ������ Allzeroframe��0��
	static void allZeroOff();

private:
	int m_mousex;
	int m_mousey;//�}�E�X���W
	int m_eFrame;//�o�߃t���[��
	Vector2 m_mousePos;

	char buf[256];
	int keyState[256];
	int keyStatePre[256];

	//setAllzeroframe�֐��Ń��b�N�����t���[���� waitframe>0�őS�z����e0�Ɂ@
	int allZeroFrame;

	//IsAll0 == true�őS�z����e0��
	bool isAllZero;
	
	void doUpdate();

	void allZero();
};


//�V���O���g��Random�N���X
class Random{
private:
	std::mt19937 mt;
	Random();

public:
	Random(const Random& r) = delete;
	Random& operator=(const Random& r) = delete;

	static Random& get();

	//SeedSetUseRD��MT�̏����l��ݒ�
	static void SeedSetUseRD();

	//MT�̏����l��Random_device���g�p���Đݒ�
	static void Initialize(int seed);

	//mt�G���W���{�̂��擾
	static std::mt19937& getMT();

	//���S����
	static unsigned int RamdomDeviceValue();

	//�ʏ��rand�擾
	static int Rand();

	//0~max�w��擾(int)
	static int Rand(int max);

	//min~max��Ԃ�(int)
	static int Rand(int min, int max);

	//1��-1��Ԃ��֐�
	static int RandPM1();

	//0~1��Ԃ�(double)
	static double Value();

	//0~max��Ԃ�(double)
	static double FRand(double max);

	//min~max��Ԃ�(double)
	static double FRand(double min, double max);

	//���K���z
	static double FRandND(double mean, double sigma);

	//���K���z ���ςƃ����W�w��
	static double FRandND(double mean, double sigma, double limit);

	//���K���z ���ςƃ����W�w��
	static double NormalDist(double ave, double range);

	//���W�A���Ŏ擾
	static double FRadRand();

	//���W�A���Ŏ擾
	static double FRadRand(double deg_min, double deg_max);
	
	//���ar�̉~��̓_��Ԃ�
	static void RandOnCircle(double r, double &x, double &y);

	//���ar�̉~��̓_��Ԃ��@���_����̊p�x���Ԃ�
	static void RandOnCircle(double r, double &x, double &y, double &ang);

	//���ar�̉~�����̓_��Ԃ�
	static void RandInCircle(double r, double &x, double &y);

	//���ar�̉~�����̓_��Ԃ��@���_����̊p�x���Ԃ�
	static void RandInCircle(double r, double &x, double &y, double &ang);

	//���ar�̉~��̓_��Ԃ�
	static Vector2 RandOnCircle(double r);

	//���ar2�̉~���甼�ar1�̉~�̗̈���������̈��̓_��Ԃ�
	static Vector2 RandOnCircle(double r1, double r2);

	//���ar�̉~�����̓_��Ԃ�
	static Vector2 RandInCircle(double r);

	//�X�N���[���̒[����50�o���_�������_���ɕԂ�
	static Vector2 RandScreenEdge();

	//�X�N���[����̃����_���ȓ_��Ԃ�
	static Vector2 RandInScreen();

	//p�̊m����true��Ԃ�
	static bool RandBool(double p);

	//�����_����HSV��Ԃ�
	static HSV RandHSV();
};

//�֐��Q
namespace Func{

	//2��
	inline double Sqr(double x);

	//���_�Ƃ̋�����Ԃ�
	double dist(double x, double y);

	//2�_�̋�����Ԃ�
	double dist(double x1, double y1, double x2, double y2);

	//2�_�̋�����2���Ԃ�
	double distSqr(double x1, double y1, double x2, double y2);

	//���όv�Z
	double Dot2D(double Ax, double Ay, double Bx, double By);

	//�O�όv�Z
	double Cross2D(double Ax, double Ay, double Bx, double By);

	//�~�`���m
	bool Circles(double x1, double y1, double r1, double x2, double y2, double r2);

	//�~�`���m
	bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2);

	//��`���m
	bool Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y);

	//��`���m
	bool Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2);

	//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_)
	bool BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad);

	//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_�܂ł̋����A�p�x)
	bool BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad);

	//�_�Ƌ�`
	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height);

	//�_�Ƌ�`
	bool BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size);

	//���ʂ̓_�Ƌ�`
	bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y);

	//�~(���acr,(cx,cy))�̋ߎ������`�Ɓ@�����`(����(rx1,ry1), �E��(rx2, ry2))�̓����蔻��
	bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2);

	//�������m(0�Ȃ炠�����ĂȂ��A0�ȏ�͂������Ă�
	double Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y);

	//�������m(0�Ȃ炠�����ĂȂ��A0�ȏ�͂������Ă�
	//Lines�œ������Ă��ꍇ�͈ʒu���v�Z�ł���
	Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y);

	//�~�Ɛ���
	bool CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey);


	//�x�N�g��
	//���_�𒆐S��ang����]
	void rotateOnZero(double &x, double &y, double ang);

	//����_(centerx,centery)�𒆐S��ang����]
	void rotateOnPoint(double &x, double &y, double centerx, double centery, double ang);

	//(���_����(sx,sy)�ւ̒P�ʃx�N�g�������߂�
	void normalizedVector(double &vx, double &vy, double sx, double sy);

	//(sx,sy)����(ex,ey)�ւ̒P�ʃx�N�g�������߂�
	void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey);

	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɑ��
	void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
	void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
	void addVector(double r, double angle, double &resultx, double &resulty);

	//�ɍ��W�\������xy�\���ɒ���
	void polarToXY(double &x, double &y, double r, double ang);

	//�p�x���v�Z
	double calAngle(double x, double y);

	//�p�x���v�Z
	double calAngle(double sx, double sy, double ex, double ey);

	//�O���t�֘A

	//3�_��ʂ钼���O���t
	double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end);

	//4�_��ʂ钼���O���t
	double graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end);

	//�x�W�F�Ȑ�  p1->p2->p3  0<t<1
	double bzCurve(double p1, double p2, double p3, double t);

	//�x�W�F�Ȑ�  p1->p2->p3  nowtime, endtime
	double bzCurve(double p1, double p2, double p3, double nowt, double endt);

	//�A�j���[�V�����p�E�_�^�_�^�_�^�ƂȂ�O���t
	int Repeat(int frame, int loop_num);

	//2���x�W�G�Ȑ����v�Z����֐�
	Vector2 GetBezier2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t);

	//2���x�W�G�Ȑ��Ő���_���ʂ�悤�Ɉ��������ꍇ�̐���_��Ԃ��֐�
	Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint);

	//Control��ʂ�2���x�W�G�Ȑ����v�Z����֐�
	Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t);

	//3���x�W�G�Ȑ����v�Z����֐�
	Vector2 GetBezier3(const Vector2& Start, const Vector2& ControlPoint1, const Vector2& ControlPoint2, const Vector2& End, float t);

	//HSV��RGB�Ɋ��Z ���ڊ֐��̈����ɓn���p
	DWORD GetColorHSV(int h, int s, int v);
	
	//HSV��setdrawbright
	void SetDrawBrightHSV(int h, int s, int v);

	//0xXXXXXX��SetDrawBright����֐�
	void SetDrawBrightInt(int col);

	//�����̊p�x,����̊p�x 2�p�̊֌W��Ԃ��@���v��葤�ɓ������ق����߂����1 �����łȂ����-1
	int absAngle(double angle1, double angle2);

	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  tarx�Ƃ̍���erange�ȉ���tarx = x�ɂ���
	void moveRate(double &x, double tarx, double rate, double eRange = 1.0);

	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
	void moveRate(double &x, double &y, double tarx, double tary, double rate, double eRangeDist = 0.5);

	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
	void moveRate(Vector2 &v2, const Vector2 &tarv2, double rate, double eRangeDist = 0.5);

	//rate��cool�̃Z�b�g��cool���X�V�Ebool��Ԃ�
	bool coolCount(int &cool);

	//��E�U���E����(�b)�E�o�߃t���[�����w�肵��sin��Ԃ�
	double sinSec(double baseVal, double A, double T, double nowFrame);

	//�X�N���[���̒��S��Ԃ�
	Vector2 getScreenCenter();

	//�X�N���[������ǂꂾ���O�ɂ��邩���v�Z���A���ȏゾ������false��Ԃ�
	bool isAlivePos(const Vector2 &pos, double length = 0.0);

	//�����_����2�����̑啶���A���t�@�x�b�g��Ԃ�
	std::string randStr();

	//�����_����N�����̑啶���A���t�@�x�b�g��Ԃ�
	std::string randStr(int n);

	//������̔z�񂩂烉���_���ȗv�f��Ԃ�
	//����Ȋ����Ŏg�� : Func::randStrVec({ "circle32", "lack_rect32" })
	std::string randStrVec(const std::vector<std::string> &strVec);

	//�O���t�B�b�N�̑傫����Ԃ�
	Vector2 getGraphSizeV2(int gHandle);

	//�������u��������
	void strReplace(std::string &target, const std::string &oldValue, const std::string &newValue);

	//�t���[���� XX:YY�̌`���ɕϊ����A���̕������Ԃ�
	std::string frameToTimeStr(int frame);

	//0xXXXXXX�̌`���Ŕw�i�F���w��
	void setBackgroundColor0x(int col);
}
