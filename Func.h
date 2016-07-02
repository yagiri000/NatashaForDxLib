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

//2015/01/04 更新

/*
class Input
class Random

namespace Func
	-当たり判定
	-ベクトル
	-イージング曲線
	-便利関数
*/



static const int LMOUSE = 250;
static const int RMOUSE = 251;

//!!!!!!!!!!!!! 注意 !!!!!!!!!!!!!
//getする前にstaticメンバにアクセスするのは不可能
//マウス座標・キー状態・起動からのフレーム数を保持するクラス
class Input{
public:

	Input();

	Input& operator=(const Input& a) = delete;
	Input(const Input& a) = delete;

	static Input& get();

	static void update();

	//キーが押されているかをboolで返す
	static bool keyNow(int i);

	//キーが押されたフレームだけtrueを返す
	static bool keyDown(int i);

	//キーが離されたフレームだけtrueを返す
	static bool keyUp(int i);

	//キーが押されているフレームを返す
	static int keyFrame(int i);

	static int mousex();

	static int mousey();

	static Vector2 mousePos();

	static int eFrame();

	//Allzeroframeの間keystateがすべて0に
	static void setAllZeroFrame(int t);

	//Allzerooffが呼ばれるまでkeystateをすべて0に
	static void allZeroOn();

	//keystateすべて0 を解除 Allzeroframeを0に
	static void allZeroOff();

private:
	int m_mousex;
	int m_mousey;//マウス座標
	int m_eFrame;//経過フレーム
	Vector2 m_mousePos;

	char buf[256];
	int keyState[256];
	int keyStatePre[256];

	//setAllzeroframe関数でロックされるフレーム数 waitframe>0で全配列内容0に　
	int allZeroFrame;

	//IsAll0 == trueで全配列内容0に
	bool isAllZero;
	
	void doUpdate();

	void allZero();
};


//シングルトンRandomクラス
class Random{
private:
	std::mt19937 mt;
	Random();

public:
	Random(const Random& r) = delete;
	Random& operator=(const Random& r) = delete;

	static Random& get();

	//SeedSetUseRDでMTの初期値を設定
	static void SeedSetUseRD();

	//MTの初期値をRandom_deviceを使用して設定
	static void Initialize(int seed);

	//mtエンジン本体を取得
	static std::mt19937& getMT();

	//完全乱数
	static unsigned int RamdomDeviceValue();

	//通常のrand取得
	static int Rand();

	//0~max指定取得(int)
	static int Rand(int max);

	//min~maxを返す(int)
	static int Rand(int min, int max);

	//1か-1を返す関数
	static int RandPM1();

	//0~1を返す(double)
	static double Value();

	//0~maxを返す(double)
	static double FRand(double max);

	//min~maxを返す(double)
	static double FRand(double min, double max);

	//正規分布
	static double FRandND(double mean, double sigma);

	//正規分布 平均とレンジ指定
	static double FRandND(double mean, double sigma, double limit);

	//正規分布 平均とレンジ指定
	static double NormalDist(double ave, double range);

	//ラジアンで取得
	static double FRadRand();

	//ラジアンで取得
	static double FRadRand(double deg_min, double deg_max);
	
	//半径rの円上の点を返す
	static void RandOnCircle(double r, double &x, double &y);

	//半径rの円上の点を返す　原点からの角度も返す
	static void RandOnCircle(double r, double &x, double &y, double &ang);

	//半径rの円内部の点を返す
	static void RandInCircle(double r, double &x, double &y);

	//半径rの円内部の点を返す　原点からの角度も返す
	static void RandInCircle(double r, double &x, double &y, double &ang);

	//半径rの円上の点を返す
	static Vector2 RandOnCircle(double r);

	//半径r2の円から半径r1の円の領域を引いた領域上の点を返す
	static Vector2 RandOnCircle(double r1, double r2);

	//半径rの円内部の点を返す
	static Vector2 RandInCircle(double r);

	//スクリーンの端から50出た点をランダムに返す
	static Vector2 RandScreenEdge();

	//スクリーン上のランダムな点を返す
	static Vector2 RandInScreen();

	//pの確率でtrueを返す
	static bool RandBool(double p);

	//ランダムなHSVを返す
	static HSV RandHSV();
};

//関数群
namespace Func{

	//2乗
	inline double Sqr(double x);

	//原点との距離を返す
	double dist(double x, double y);

	//2点の距離を返す
	double dist(double x1, double y1, double x2, double y2);

	//2点の距離の2乗を返す
	double distSqr(double x1, double y1, double x2, double y2);

	//内積計算
	double Dot2D(double Ax, double Ay, double Bx, double By);

	//外積計算
	double Cross2D(double Ax, double Ay, double Bx, double By);

	//円形同士
	bool Circles(double x1, double y1, double r1, double x2, double y2, double r2);

	//円形同士
	bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2);

	//矩形同士
	bool Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y);

	//矩形同士
	bool Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2);

	//点と幅のある線 (点の座標、幅のある線の始点・終点)
	bool BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad);

	//点と幅のある線 (点の座標、幅のある線の始点・終点までの距離、角度)
	bool BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad);

	//点と矩形
	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height);

	//点と矩形
	bool BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size);

	//普通の点と矩形
	bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y);

	//円(半径cr,(cx,cy))の近似正方形と　長方形(左上(rx1,ry1), 右下(rx2, ry2))の当たり判定
	bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2);

	//線分同士(0ならあたってない、0以上はあたってる
	double Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y);

	//線分同士(0ならあたってない、0以上はあたってる
	//Linesで当たってた場合は位置を計算できる
	Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y);

	//円と線分
	bool CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey);


	//ベクトル
	//原点を中心にang分回転
	void rotateOnZero(double &x, double &y, double ang);

	//ある点(centerx,centery)を中心にang分回転
	void rotateOnPoint(double &x, double &y, double centerx, double centery, double ang);

	//(原点から(sx,sy)への単位ベクトルを求める
	void normalizedVector(double &vx, double &vy, double sx, double sy);

	//(sx,sy)から(ex,ey)への単位ベクトルを求める
	void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey);

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに代入
	void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	void addVector(double r, double angle, double &resultx, double &resulty);

	//極座標表現からxy表現に直す
	void polarToXY(double &x, double &y, double r, double ang);

	//角度を計算
	double calAngle(double x, double y);

	//角度を計算
	double calAngle(double sx, double sy, double ex, double ey);

	//グラフ関連

	//3点を通る直線グラフ
	double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end);

	//4点を通る直線グラフ
	double graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end);

	//ベジェ曲線  p1->p2->p3  0<t<1
	double bzCurve(double p1, double p2, double p3, double t);

	//ベジェ曲線  p1->p2->p3  nowtime, endtime
	double bzCurve(double p1, double p2, double p3, double nowt, double endt);

	//アニメーション用・＼／＼／＼／となるグラフ
	int Repeat(int frame, int loop_num);

	//2次ベジエ曲線を計算する関数
	Vector2 GetBezier2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t);

	//2次ベジエ曲線で制御点も通るように引きたい場合の制御点を返す関数
	Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint);

	//Controlを通る2次ベジエ曲線を計算する関数
	Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t);

	//3次ベジエ曲線を計算する関数
	Vector2 GetBezier3(const Vector2& Start, const Vector2& ControlPoint1, const Vector2& ControlPoint2, const Vector2& End, float t);

	//HSVをRGBに換算 直接関数の引数に渡す用
	DWORD GetColorHSV(int h, int s, int v);
	
	//HSVでsetdrawbright
	void SetDrawBrightHSV(int h, int s, int v);

	//0xXXXXXXでSetDrawBrightする関数
	void SetDrawBrightInt(int col);

	//自分の角度,相手の角度 2角の関係を返す　時計回り側に動いたほうが近ければ1 そうでなければ-1
	int absAngle(double angle1, double angle2);

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  tarxとの差がerange以下でtarx = xにする
	void moveRate(double &x, double tarx, double rate, double eRange = 1.0);

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	void moveRate(double &x, double &y, double tarx, double tary, double rate, double eRangeDist = 0.5);

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	void moveRate(Vector2 &v2, const Vector2 &tarv2, double rate, double eRangeDist = 0.5);

	//rateとcoolのセットのcoolを更新・boolを返す
	bool coolCount(int &cool);

	//基準・振幅・周期(秒)・経過フレームを指定してsinを返す
	double sinSec(double baseVal, double A, double T, double nowFrame);

	//スクリーンの中心を返す
	Vector2 getScreenCenter();

	//スクリーンからどれだけ外にいるかを計算し、一定以上だったらfalseを返す
	bool isAlivePos(const Vector2 &pos, double length = 0.0);

	//ランダムな2文字の大文字アルファベットを返す
	std::string randStr();

	//ランダムなN文字の大文字アルファベットを返す
	std::string randStr(int n);

	//文字列の配列からランダムな要素を返す
	//こんな感じで使う : Func::randStrVec({ "circle32", "lack_rect32" })
	std::string randStrVec(const std::vector<std::string> &strVec);

	//グラフィックの大きさを返す
	Vector2 getGraphSizeV2(int gHandle);

	//文字列を置き換える
	void strReplace(std::string &target, const std::string &oldValue, const std::string &newValue);

	//フレームを XX:YYの形式に変換し、その文字列を返す
	std::string frameToTimeStr(int frame);

	//0xXXXXXXの形式で背景色を指定
	void setBackgroundColor0x(int col);
}
