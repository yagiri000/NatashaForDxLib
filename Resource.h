//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once

#include "DxLib.h"
#include <string>
#include <utility>
#include <unordered_map>


class GraphAE{
public:
	//�V���O���g��
	GraphAE& operator=(const GraphAE& a) = delete;
	GraphAE(const GraphAE& a) = delete;
	static GraphAE& get();
	void load();

	//�n���h���擾
	static int handle(std::string name, int num);

	void LoadToMap(std::string name);
private:
	std::unordered_map<std::string, int> handlemap;
	GraphAE();
};

class GraphButton{
public:
	//�V���O���g��
	GraphButton& operator=(const GraphButton& a) = delete;
	GraphButton(const GraphButton& a) = delete;
	static GraphButton& get();

	//�f�[�^�����[�h
	void load();

	//�n���h���擾
	static int handle(std::string name, int isSelecting);

private:
	std::unordered_map<std::string, std::pair<int, int>> handlemap;

	GraphButton();

	//png�̂ݓǂݍ��� Images�t�H���_������
	void LoadToMap(std::string name);
};



class GraphBullet{
public:
	//�V���O���g��
	GraphBullet& operator=(const GraphBullet& a) = delete;
	GraphBullet(const GraphBullet& a) = delete;
	static GraphBullet& get();
	void load();

	static const int colorNum = 36;

	struct HandleArray{
		int arr[colorNum];
	};

	//�n���h���擾
	static int handle(std::string name, int num);
	//�n���h���擾�@ hue��1.0����
	static int handled(std::string name, double hue);


private:
	std::unordered_map<std::string, HandleArray> handlemap;

	//png�̂ݓǂݍ���
	GraphBullet();
	//png�̂ݓǂݍ��� Images�t�H���_������
	void LoadToMap(std::string name);
};

using GraphB = GraphBullet;



class GraphHue{
public:
	//�V���O���g��
	GraphHue& operator=(const GraphHue& a) = delete;
	GraphHue(const GraphHue& a) = delete;
	static GraphHue& get();
	void load();

	static const int colorNum = 36;

	struct HandleArray{
		int arr[colorNum];
	};

	//�n���h���擾
	static int handle(std::string name, int num);
	//�n���h���擾�@ hue��1.0����
	static int handled(std::string name, double hue);


private:
	std::unordered_map<std::string, HandleArray> handlemap;

	//png�̂ݓǂݍ���
	GraphHue();
	//png�̂ݓǂݍ��� Images�t�H���_������
	void LoadToMap(std::string name);
};


class Graph{
public:
	//�V���O���g��
	Graph& operator=(const Graph& a) = delete;
	Graph(const Graph& a) = delete;
	static Graph& get();
	void load();

	//�n���h���擾
	static int handle(std::string name);

	void LoadToMap(std::string name);
private:
	std::unordered_map<std::string, int> handlemap;
	Graph();
};


class GraphDiv{
public:
	//�V���O���g��
	GraphDiv& operator=(const GraphDiv& a) = delete;
	GraphDiv(const GraphDiv& a) = delete;
	static GraphDiv& get();
	void load();

	//�n���h���擾
	static int handle(std::string name, int num);

	class gh_array{
		static const int ary_num = 512;
	public:
		int arr[ary_num];
	};

private:
	std::unordered_map<std::string, gh_array> handlemap;

	//png�̂ݓǂݍ���
	GraphDiv();

	//png�̂ݓǂݍ��� Images�t�H���_������
	void LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize);
	void LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick);
};





class Font{
public:
	//�V���O���g��
	Font& operator=(const Font& a) = delete;
	Font(const Font& a) = delete;
	static Font& get();
	void load();

	int operator()(std::string name);
	//�n���h���擾
	static int handle(std::string name);
	static int def();
	std::string defalutFontName;

private:
	std::unordered_map<std::string, int> handlemap;
	Font();

	//�t�H���g�ǂݍ��݁i���ł�OS�ɓo�^�ς݂̂��́j
	void LoadFont(std::string reg_name, std::string font_name, int fontsize, int thick);
	//�t�H���g�ǂݍ���
	void LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick);
};

extern Font& font;



class SoundHandle{
public:
	int handle;
	const double volume;	// 0.0 ~ 1.0
	int play_cool;	// < 0�ōĐ����Ȃ�
	const int play_rate;	//�Đ��Ԋu (���ʉ��Ȃǂ��A���ōĐ�����Ƃ��̊Ԋu�j0��1�t���[�����ɍĐ��\

	SoundHandle();
	SoundHandle(int handle_, double volume_ = 1.0, int play_rate_ = 0);
	void SetVolume(double master);
};

class Sound{
public:

	//�V���O���g��
	Sound& operator=(const Sound& a) = delete;
	Sound(const Sound& a) = delete;
	static Sound& get();
	void load();

	//�n���h�����擾
	static int handle(std::string name);

	//��񂾂��Đ�
	static void playone(std::string name);

	//���[�v�Đ�
	static void playloop(std::string name);

	//BGM�Đ� BGM�͏펞�����
	static void playbgm(std::string name);

	//BGM��~
	static void stopbgm();

	//�Đ����̉������ׂĒ�~
	static void stopall();

	//�w�肵�����̍Đ����~
	static void stopone(std::string name);

	//�{�����[�����Z�b�g
	static void setvolume(double master);

	//�Đ��Ԋu�t���[�����X�V
	static void update();

private:
	int bgmhandle = -1;
	double masterVolume = 1.0;
	std::unordered_map<std::string, SoundHandle> handlemap;

	Sound();
	void LoadToMap(std::string name);
	void LoadToMap(std::string name, double volume, int play_rate);
};