#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class Dir
{
public:
	// �R���X�g���N�^
	Dir(void);
	// �f�X�g���N�^
	virtual ~Dir(void);
	// �t�@�C���ꗗ�擾
	// folder : �t�H���_�̐�΃p�X����͂Ƃ��� 
	// �� : "D:\\Users\\Pictures\\"
	static vector<string> read(string folder);
};