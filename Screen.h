//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once

#include <string>
#include <deque>
#include "Abstract.h"
#include "Easing.h"

//pImpl
class IScreenEffect;
class IScreenDraw;

class ScreenDrawEffectMgr{
public:
	std::vector<std::shared_ptr<IScreenEffect>> effectList;
	std::shared_ptr<IScreenDraw> drawObj;
	ScreenDrawEffectMgr();
	void addEffect(const std::shared_ptr<IScreenEffect> &ptr);
	void addDraw(const std::shared_ptr<IScreenDraw> &ptr);
	void update();
	void draw();
};

class Screen{
public:
	//�V���O���g��
	Screen& operator=(const Screen& a) = delete;
	Screen(const Screen& a) = delete;
	static Screen& get();

	//�X�N���[���T�C�Y
	const int width;
	const int height;

	int afterImageAlpha;

	//�X�N���[��
	int mainScreen;		//��ɂ���ɕ`�悷��
	int afterImageScreen;//�c���p���C���[
	int tmpScreen;
	int subScreen; //�V�F�[�_�[�K�p�p
	int scopeScreen;

	ScreenDrawEffectMgr screenDrawEffectMgr;

	//���t���[���F�����]
	static void setReverseHue(int frame);

	//���t���[�����]
	static void setInvert(int frame);

	//���t���[���K�E�X
	static void setGauss(int frame);

	//���t���[���Ó]
	static void setBlackOut(int frame);

	//���t���[�����]
	static void setWhiteOut(int frame);

	//���t���[���ʓx������
	static void setSaturation(int frame);
	
	//���t���[���Ó]���K�E�X
	static void setTransition(int frame);

	//�w��t���[���X�N���[�����g�債�ďk������
	static void setExtendScreen(int frame);

	//�X�N���[���h���ݒ�
	static void setShake(int frame, int distance = 20);

	// �K�E�X�t�B���^�[���{��
	static void Gauss(int pal_1 = 8, int pal_2 = 1000);

	// HSB�t�B���^�[���{��
	static void HSB(int type, int hue, int saturation, int bright);

	// �K�����]�t�B���^�[���{��
	static void Invert();

	// Level�t�B���^�[���{��
	static void Level(int min, int max, int gamma, int afterMin, int afterMax);

	// �O���f�[�V�����}�b�v�t�B���^�[���{��
	static void GradiendMap(int handle);

	//�`��J�n
	static void DrawStart();

	//�V�F�[�_�[�Ƃ��K�p���鎞�p
	static void SetDrawScreenSub();

	//�V�F�[�_�[�Ƃ��K�p�������Ɨp
	static void SetDrawScreenMain();

	//�`��I���E�t���b�v
	static void DrawEnd();


	//�c�����C���[�Ɍ��݂̃��C���[���R�s�[
	static void SetAfterImageScreen();

	//�c�����C���[��`��
	static void DrawAfterImageScreen();

private:
	Screen();
	void init();
};


