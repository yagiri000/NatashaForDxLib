#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class Dir
{
public:
	// コンストラクタ
	Dir(void);
	// デストラクタ
	virtual ~Dir(void);
	// ファイル一覧取得
	// folder : フォルダの絶対パスを入力とする 
	// 例 : "D:\\Users\\Pictures\\"
	static vector<string> read(string folder);
};