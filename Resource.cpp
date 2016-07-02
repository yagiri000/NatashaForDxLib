#pragma once
#include "Resource.h"
#include "Func.h"
#include "Dir.h"


//���[�h����t�H���_��Images�ł����āAImages.dxa�ł͂Ȃ��̂Œ���




void GraphAE::load(){
	std::vector<std::string> fileVec = Dir::read("ImagesAE");
	for (auto i = fileVec.begin(); i < fileVec.end(); i++){
		LoadToMap(i->c_str());
	}
}

void GraphButton::load(){
	LoadToMap("button.png");
}

void GraphBullet::load(){
	LoadToMap("circle32.png");
}

void GraphHue::load(){
	std::vector<std::string> fileVec = Dir::read("ImagesHue");
	for (auto i = fileVec.begin(); i < fileVec.end(); i++){
		LoadToMap(i->c_str());
	}
}

void Graph::load(){
	std::vector<std::string> fileVec = Dir::read("Images");
	for (auto i = fileVec.begin(); i < fileVec.end(); i++){
		LoadToMap(i->c_str());
	}
}

void GraphDiv::load(){
	LoadToMap("box_blank.png", 16, 4, 4, 64, 64);
	LoadToMap("cir_blank.png", 16, 4, 4, 64, 64);
	LoadToMap("title_str.png", 8, 1, 8, 512, 64);
}


void Sound::load(){
	std::vector<std::string> fileVec = Dir::read("Sounds");
	for (auto i = fileVec.begin(); i < fileVec.end(); i++){
		LoadToMap(i->c_str());
	}
}

void Font::load(){
	defalutFontName = "SegoeUI18";
	LoadFont("SegoeUI12", "Segoe UI", 12, 3);
	LoadFont("SegoeUI18", "Segoe UI", 18, 3);
	LoadFont("SegoeUI50", "Segoe UI", 50, 3);
	LoadFont("MM18", "", 18, 3);

	std::string ttfName = "ostrich-regular.ttf";
	std::string fontName = "Ostrich Sans";
	LoadFont("OS12", ttfName.c_str(), fontName.c_str(), 12, 9);
	LoadFont("OS14", ttfName.c_str(), fontName.c_str(), 14, 9);
	LoadFont("OS18", ttfName.c_str(), fontName.c_str(), 18, 7);
	LoadFont("OS50", ttfName.c_str(), fontName.c_str(), 50, 9);
}


GraphAE::GraphAE(){
}

GraphAE& GraphAE::get(){
	static GraphAE inst;
	return inst;
}

//�n���h���擾
int GraphAE::handle(std::string name, int num){
	std::string loadHandleName = name + std::to_string(num);
	if (get().handlemap.find(loadHandleName) == get().handlemap.end()){
		std::string log = "GraphAE::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(loadHandleName);
}

void GraphAE::LoadToMap(std::string name){
	int gh;
	std::string loadname = "ImagesAE/" + name;
	gh = LoadGraph(loadname.c_str());
	if (gh != -1){
		std::vector<std::string> extensionList = { ".png", ".jpg" };
		for (auto &i : extensionList){
			Func::strReplace(name, i, "");
		}
		handlemap.emplace(name, gh);
		return;
	}
}

GraphBullet::GraphBullet(){
}

GraphBullet& GraphBullet::get(){
	static GraphBullet inst;
	return inst;
}

void GraphBullet::LoadToMap(std::string name){
	std::string loadname = "ImagesHue/" + name;
	HandleArray hArray;
	int tmp_handle = LoadGraph(loadname.c_str());
	int sizeX, sizeY;
	GetGraphSize(tmp_handle, &sizeX, &sizeY);
	for (int i = 0; i < colorNum; i++){
		hArray.arr[i] = MakeScreen(sizeX, sizeY, TRUE);
		SetDrawScreen(hArray.arr[i]);
		int hue = i * 360 / colorNum;
		int easeV = 0;
		if (abs(hue - 60) < 15){
			easeV = 1.5 * (15 - abs(hue - 60));
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		Func::SetDrawBrightHSV(hue, 220, 255 - easeV);
		//5��`�悷�邱�ƂŔ������̍����ۂ�����������
		for (int i = 0; i < 5; i++){
			DrawGraph(0, 0, tmp_handle, TRUE);
		}
	}
	SetDrawBright(255, 255, 255);

	std::vector<std::string> extensionList = { ".png", ".jpg" };
	for (auto &i : extensionList){
		Func::strReplace(name, i, "");
	}

	handlemap.emplace(name, hArray);
}

int GraphBullet::handle(std::string name, int num){
	if (num < 0){
		num %= colorNum;
		num += colorNum;
	}
	else{
		num %= colorNum;
	}
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphBullet::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}

	return get().handlemap.at(name).arr[num];
}

int GraphBullet::handled(std::string name, double hue){
	hue = fmod(hue, 1.0);
	if (hue < 0.0){
		hue += 1.0;
	}
	int num = (int)(hue * colorNum) % colorNum;
	if (num < 0){
		std::string log = "GraphBullet::handled�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
		num = 0;
	}
	if (num >= 36){
		num = 36;
	}

	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphBullet::handled�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}


GraphButton::GraphButton(){

}

GraphButton& GraphButton::get(){
	static GraphButton inst;
	return inst;
}

void GraphButton::LoadToMap(std::string name){
	std::string loadname = "Images/" + name;
	std::pair<int, int> handle;
	handle.first = LoadGraph(loadname.c_str());
	handle.second = LoadGraph(loadname.c_str());
	GraphFilter(handle.second, DX_GRAPH_FILTER_HSB, 0, 0, 0, 256);

	std::vector<std::string> extensionList = { ".png", ".jpg" };
	for (auto &i : extensionList){
		Func::strReplace(name, i, "");
	}

	handlemap.emplace(name, handle);
}

int GraphButton::handle(std::string name, int isSelecting){
	if (isSelecting == 0){
		return get().handlemap.at(name).first;
	}
	else{
		return get().handlemap.at(name).second;
	}
}



GraphHue::GraphHue(){

}

GraphHue& GraphHue::get(){
	static GraphHue inst;
	return inst;
}

void GraphHue::LoadToMap(std::string name){
	std::string loadname = "ImagesHue/" + name;
	HandleArray hArray;
	int tmp_handle = LoadGraph(loadname.c_str());
	int sizeX, sizeY;
	GetGraphSize(tmp_handle, &sizeX, &sizeY);
	for (int i = 0; i < colorNum; i++){
		hArray.arr[i] = MakeScreen(sizeX, sizeY, TRUE);
		SetDrawScreen(hArray.arr[i]);
		int hue = i * 360 / colorNum;
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		Func::SetDrawBrightHSV(hue, 140, 255);
		//5��`�悷�邱�ƂŔ������̍����ۂ�����������
		for (int i = 0; i < 5; i++){
			DrawGraph(0, 0, tmp_handle, TRUE);
		}
	}
	SetDrawBright(255, 255, 255);

	std::vector<std::string> extensionList = { ".png", ".jpg" };
	for (auto &i : extensionList){
		Func::strReplace(name, i, "");
	}

	handlemap.emplace(name, hArray);
}

int GraphHue::handle(std::string name, int num){
	if (num < 0){
		num %= colorNum;
		num += colorNum;
	}
	else{
		num %= colorNum;
	}
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphHue::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}

int GraphHue::handled(std::string name, double hue){
	hue = fmod(hue, 1.0);
	if (hue < 0.0){
		hue += 1.0;
	}
	int num = (int)(hue * colorNum) % colorNum;
	if (num < 0){
		std::string log = "GraphHue::handled�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
		num = 0;
	}
	if (num >= 36){
		num = 36;
	}

	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphHue::handled�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}



Graph::Graph(){
}

Graph& Graph::get(){
	static Graph inst;
	return inst;
}

//�n���h���擾
int Graph::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Graph::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name);
}

void Graph::LoadToMap(std::string name){
	int gh;
	std::string loadname = "Images/" + name;
	gh = LoadGraph(loadname.c_str());
	if (gh != -1){
		std::vector<std::string> extensionList = { ".png", ".jpg" };
		for (auto &i : extensionList){
			Func::strReplace(name, i, "");
		}
		handlemap.emplace(name, gh);
		return;
	}
}



GraphDiv::GraphDiv(){
}
GraphDiv& GraphDiv::get(){
	static GraphDiv inst;
	return inst;
}

//�n���h���擾
int GraphDiv::handle(std::string name, int num){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphDiv::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}


void GraphDiv::LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize){
	std::string loadname = "ImagesDiv/" + name;
	gh_array gh_array_;
	LoadDivGraph(loadname.c_str(), AllNum, XNum, YNum, XSize, YSize, &gh_array_.arr[0]);

	std::vector<std::string> extensionList = { ".png", ".jpg" };
	for (auto &i : extensionList){
		Func::strReplace(name, i, "");
	}
	handlemap.emplace(name, gh_array_);
}



Font::Font(){
}

Font& Font::get(){
	static Font inst;
	return inst;
}

int Font::operator()(std::string name){
	return handle(name);
}

//�n���h���擾
int Font::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Font::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name);
}

//�n���h���擾
int Font::def(){
	return get().handlemap.at(get().defalutFontName);
}

Font& font = Font::get();

//�o�^���E�t�@�C���̃p�X�E�t�H���g�̖��O���w��iPC�Ɍ���������Ă�����́j
//ex ("HG96", "Hogeman's_Font", 96, 5)
void Font::LoadFont(std::string reg_name, std::string font_name, int fontsize, int thick){
	int tmp_handle = CreateFontToHandle(font_name.c_str(), fontsize, thick, DX_FONTTYPE_ANTIALIASING_4X4);
	handlemap.emplace(reg_name.c_str(), tmp_handle);
}

//�o�^���E�t�@�C���̃p�X�E�t�H���g�̖��O���w��
//ex ("HG96", "hoge.ttf", "Hogeman's_Font", 96, 5)
void Font::LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick){

	file_path = "Fonts/" + file_path;
	const char* filename = file_path.c_str();

	// �t�@�C���̃T�C�Y�𓾂�
	int FontFileSize = FileRead_size(filename);
	// �t�H���g�t�@�C�����J��
	int FontFileHandle = FileRead_open(filename);
	// �t�H���g�f�[�^�i�[�p�̃������̈���m��
	void *Buffer = malloc(FontFileSize);
	// �t�H���g�t�@�C�����ۂ��ƃ������ɓǂݍ���
	FileRead_read(Buffer, FontFileSize, FontFileHandle);
	// AddFontMemResourceEx�����p
	DWORD font_num = 0;
	// �������ɓǂݍ��񂾃t�H���g�f�[�^���V�X�e���ɒǉ�
	if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) != 0){}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	int tmp_handle = CreateFontToHandle(font_name.c_str(), fontsize, thick, DX_FONTTYPE_ANTIALIASING_4X4);
	handlemap.emplace(reg_name.c_str(), tmp_handle);
}



SoundHandle::SoundHandle() :
handle(0),
volume(0),
play_cool(0),
play_rate(0)
{
}

SoundHandle::SoundHandle(int handle_, double volume_, int play_rate_) :
handle(handle_),
volume(volume_),
play_cool(0),
play_rate(play_rate_)
{
}

void SoundHandle::SetVolume(double master)
{
	ChangeVolumeSoundMem(master * volume * 255.0, handle);
}

Sound::Sound(){
}

Sound& Sound::get(){
	static Sound inst;
	return inst;
}

//�n���h�����擾
int Sound::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Sound::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap[name].handle;
}

//��񂾂��Đ�
void Sound::playone(std::string name){
	auto &a = get().handlemap[name];
	if (a.play_cool <= 0){
		PlaySoundMem(get().handle(name), DX_PLAYTYPE_BACK);
		a.play_cool = a.play_rate;
	}
}

//���[�v�Đ�
void Sound::playloop(std::string name){
	PlaySoundMem(get().handle(name), DX_PLAYTYPE_LOOP);
}

//BGM�Đ� BGM�͏펞�����
void Sound::playbgm(std::string name){
	StopSoundMem(get().bgmhandle);
	get().bgmhandle = get().handle(name);
	PlaySoundMem(get().bgmhandle, DX_PLAYTYPE_LOOP);
}

//BGM��~
void Sound::stopbgm(){
	StopSoundMem(get().bgmhandle);
}

//�Đ����̉������ׂĒ�~
void Sound::stopall(){
	for (auto &i : get().handlemap){
		StopSoundMem(i.second.handle);
	}
}

//�w�肵�����̍Đ����~
void Sound::stopone(std::string name){
	StopSoundMem(get().handle(name));
}

//�{�����[�����Z�b�g
void Sound::setvolume(double master)
{
	get().masterVolume = master;
	for (auto &i : get().handlemap){
		i.second.SetVolume(get().masterVolume);
	}
}

//�Đ��Ԋu�t���[�����X�V
void Sound::update()
{
	for (auto &i : get().handlemap){
		if (i.second.play_cool > 0){
			i.second.play_cool--;
		}
	}
}

void Sound::LoadToMap(std::string name){
	int tmphandle;
	std::string loadname = "Sounds/" + name;
	tmphandle = LoadSoundMem(loadname.c_str());
	if (tmphandle != -1){
		std::vector<std::string> extensionList = { ".wav", ".ogg", ".mp3" };
		for (auto &i : extensionList){
			Func::strReplace(name, i, "");
		}

		handlemap.emplace(name, SoundHandle(tmphandle));
		return;
	}
	OutputDebugString(("\n" + name + " is not exist\n").c_str());
	//assert(1 == 0 && "sound file is not exist" && name.c_str());
}

void Sound::LoadToMap(std::string name, double volume, int play_rate){
	int tmphandle;
	std::string loadname = "Sounds/" + name;
	tmphandle = LoadSoundMem(loadname.c_str());
	if (tmphandle != -1){
		std::vector<std::string> extensionList = { ".wav", ".ogg", ".mp3" };
		for (auto &i : extensionList){
			Func::strReplace(name, i, "");
		}
		handlemap.emplace(name, SoundHandle(tmphandle, volume, play_rate));
		return;
	}
	OutputDebugString(("\n" + name + " is not exist\n").c_str());
}

