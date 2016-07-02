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
	//シングルトン
	GraphAE& operator=(const GraphAE& a) = delete;
	GraphAE(const GraphAE& a) = delete;
	static GraphAE& get();
	void load();

	//ハンドル取得
	static int handle(std::string name, int num);

	void LoadToMap(std::string name);
private:
	std::unordered_map<std::string, int> handlemap;
	GraphAE();
};

class GraphButton{
public:
	//シングルトン
	GraphButton& operator=(const GraphButton& a) = delete;
	GraphButton(const GraphButton& a) = delete;
	static GraphButton& get();

	//データをロード
	void load();

	//ハンドル取得
	static int handle(std::string name, int isSelecting);

private:
	std::unordered_map<std::string, std::pair<int, int>> handlemap;

	GraphButton();

	//pngのみ読み込み Imagesフォルダを見る
	void LoadToMap(std::string name);
};



class GraphBullet{
public:
	//シングルトン
	GraphBullet& operator=(const GraphBullet& a) = delete;
	GraphBullet(const GraphBullet& a) = delete;
	static GraphBullet& get();
	void load();

	static const int colorNum = 36;

	struct HandleArray{
		int arr[colorNum];
	};

	//ハンドル取得
	static int handle(std::string name, int num);
	//ハンドル取得　 hueは1.0周期
	static int handled(std::string name, double hue);


private:
	std::unordered_map<std::string, HandleArray> handlemap;

	//pngのみ読み込み
	GraphBullet();
	//pngのみ読み込み Imagesフォルダを見る
	void LoadToMap(std::string name);
};

using GraphB = GraphBullet;



class GraphHue{
public:
	//シングルトン
	GraphHue& operator=(const GraphHue& a) = delete;
	GraphHue(const GraphHue& a) = delete;
	static GraphHue& get();
	void load();

	static const int colorNum = 36;

	struct HandleArray{
		int arr[colorNum];
	};

	//ハンドル取得
	static int handle(std::string name, int num);
	//ハンドル取得　 hueは1.0周期
	static int handled(std::string name, double hue);


private:
	std::unordered_map<std::string, HandleArray> handlemap;

	//pngのみ読み込み
	GraphHue();
	//pngのみ読み込み Imagesフォルダを見る
	void LoadToMap(std::string name);
};


class Graph{
public:
	//シングルトン
	Graph& operator=(const Graph& a) = delete;
	Graph(const Graph& a) = delete;
	static Graph& get();
	void load();

	//ハンドル取得
	static int handle(std::string name);

	void LoadToMap(std::string name);
private:
	std::unordered_map<std::string, int> handlemap;
	Graph();
};


class GraphDiv{
public:
	//シングルトン
	GraphDiv& operator=(const GraphDiv& a) = delete;
	GraphDiv(const GraphDiv& a) = delete;
	static GraphDiv& get();
	void load();

	//ハンドル取得
	static int handle(std::string name, int num);

	class gh_array{
		static const int ary_num = 512;
	public:
		int arr[ary_num];
	};

private:
	std::unordered_map<std::string, gh_array> handlemap;

	//pngのみ読み込み
	GraphDiv();

	//pngのみ読み込み Imagesフォルダを見る
	void LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize);
	void LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick);
};





class Font{
public:
	//シングルトン
	Font& operator=(const Font& a) = delete;
	Font(const Font& a) = delete;
	static Font& get();
	void load();

	int operator()(std::string name);
	//ハンドル取得
	static int handle(std::string name);
	static int def();
	std::string defalutFontName;

private:
	std::unordered_map<std::string, int> handlemap;
	Font();

	//フォント読み込み（すでにOSに登録済みのもの）
	void LoadFont(std::string reg_name, std::string font_name, int fontsize, int thick);
	//フォント読み込み
	void LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick);
};

extern Font& font;



class SoundHandle{
public:
	int handle;
	const double volume;	// 0.0 ~ 1.0
	int play_cool;	// < 0で再生しない
	const int play_rate;	//再生間隔 (効果音などが連続で再生するときの間隔）0で1フレーム毎に再生可能

	SoundHandle();
	SoundHandle(int handle_, double volume_ = 1.0, int play_rate_ = 0);
	void SetVolume(double master);
};

class Sound{
public:

	//シングルトン
	Sound& operator=(const Sound& a) = delete;
	Sound(const Sound& a) = delete;
	static Sound& get();
	void load();

	//ハンドルを取得
	static int handle(std::string name);

	//一回だけ再生
	static void playone(std::string name);

	//ループ再生
	static void playloop(std::string name);

	//BGM再生 BGMは常時一つだけ
	static void playbgm(std::string name);

	//BGM停止
	static void stopbgm();

	//再生中の音をすべて停止
	static void stopall();

	//指定した音の再生を停止
	static void stopone(std::string name);

	//ボリュームをセット
	static void setvolume(double master);

	//再生間隔フレームを更新
	static void update();

private:
	int bgmhandle = -1;
	double masterVolume = 1.0;
	std::unordered_map<std::string, SoundHandle> handlemap;

	Sound();
	void LoadToMap(std::string name);
	void LoadToMap(std::string name, double volume, int play_rate);
};