#include "Func.h"

Input::Input() :
m_mousex(0),
m_mousey(0),
m_eFrame(0),
allZeroFrame(0),
isAllZero(false)
{
}

Input& Input::get(){
	static Input inp;
	return inp;
}

void Input::update(){
	get().doUpdate();
}

//キーが押されているかをboolで返す
bool Input::keyNow(int i){
	return get().keyState[i] > 0;
}

//キーが押されたフレームだけtrueを返す
bool Input::keyDown(int i){
	return (get().keyState[i] == 1 && get().keyStatePre[i] != -1);
}

//キーが離されたフレームだけtrueを返す
bool Input::keyUp(int i){
	return (get().keyState[i] == 0) && (get().keyStatePre[i] > 0);
}

//キーが押されているフレームを返す
int Input::keyFrame(int i){
	return get().keyState[i];
}

int Input::mousex(){
	return get().m_mousex;
}

int Input::mousey(){
	return get().m_mousey;
}

Vector2 Input::mousePos(){
	return get().m_mousePos;
}

int Input::eFrame(){
	return get().m_eFrame;
}

//allZeroFrameの間keyStateがすべて0に
void Input::setAllZeroFrame(int t){
	if (t > 0){
		get().allZeroFrame = t;
	}
}

//Allzerooffが呼ばれるまでkeyStateをすべて0に
void Input::allZeroOn(){
	get().isAllZero = true;
}

//keyStateすべて0 を解除 allZeroFrameを0に
void Input::allZeroOff(){
	get().isAllZero = false;
	get().allZeroFrame = 0;
}


void Input::doUpdate(){
	GetHitKeyStateAll(buf);
	buf[LMOUSE] = GetMouseInput() & MOUSE_INPUT_LEFT;
	buf[RMOUSE] = ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0) ? 0 : 1;
	for (int i = 0; i < 256; i++){
		//1フレーム前の情報を保存
		keyStatePre[i] = keyState[i];
		//keyStateを更新
		if (buf[i] == 1){
			if (keyState[i] == -1) keyState[i] = 0;
			keyState[i]++;
		}
		else{
			keyState[i] = 0;
		}
	}
	if (isAllZero == true || allZeroFrame > 0){
		allZero();
	}
	if (allZeroFrame > 0){
		allZeroFrame--;
	}
	//マウス座標更新
	GetMousePoint(&m_mousex, &m_mousey);
	m_mousePos.Set(m_mousex, m_mousey);
	//経過フレーム計測
	m_eFrame++;
}

void Input::allZero(){
	for (int i = 0; i < 256; i++){
		keyState[i] = -1;
		keyStatePre[i] = -1;
	}
}

//class Random
Random::Random(){
	//SeedSetUseRDでMTの初期値を設定
	SeedSetUseRD();
}

Random& Random::get()
{
	static Random r;
	return r;
}

//MTの初期値をRandom_deviceを使用して設定
void Random::SeedSetUseRD(){
	std::random_device r;
	get().mt.seed(r());
}
//MTの初期値設定
void Random::Initialize(int seed)
{
	get().mt.seed(seed);
}
//mtエンジン本体を取得
std::mt19937& Random::getMT(){
	return get().mt;
}

//完全乱数
unsigned int Random::RamdomDeviceValue()
{
	std::random_device r;
	return r();
}

//通常のrand取得
int Random::Rand(){
	return get().mt();
}
//0~max指定取得(int)
int Random::Rand(int max)
{
	std::uniform_int_distribution<int> uid(0, max);
	return uid(get().mt);
}
//min~maxを返す(int)
int Random::Rand(int min, int max)
{
	if (min > max){
		int tmp = min;
		min = max;
		max = tmp;
	}
	std::uniform_int_distribution<int> uid(min, max);
	return uid(get().mt);
}
//1か-1を返す関数
int Random::RandPM1(){
	std::uniform_int_distribution<int> uid(0, 1);
	return uid(get().mt) * 2 - 1;
}
//0~1を返す(double)
double Random::Value()
{
	std::uniform_real_distribution<double> urd(0, 1);
	return urd(get().mt);
}
//0~maxを返す(double)
double Random::FRand(double max)
{
	if (max < 0.0){
		return 0.0;
	}
	std::uniform_real_distribution<double> urd(0, max);
	return urd(get().mt);
}
//min~maxを返す(double)
double Random::FRand(double min, double max)
{
	if (min > max){
		double tmp = min;
		min = max;
		max = tmp;
	}
	std::uniform_real_distribution<double> urd(min, max);
	return urd(get().mt);
}
//正規分布
double Random::FRandND(double mean, double sigma)
{
	std::normal_distribution<double> nd(mean, sigma);
	return nd(get().mt);
}
double Random::FRandND(double mean, double sigma, double limit)
{
	std::normal_distribution<double> nd(mean, sigma);
	double r = nd(get().mt);
	if (r < mean - limit)
		r = mean - limit;
	if (r > mean + limit)
		r = mean + limit;
	return r;
}
//正規分布 平均とレンジ指定
double Random::NormalDist(double ave, double range){
	std::normal_distribution<double> nd(ave, range / 3.0);
	double ret = nd(get().mt);
	if (ret < ave - range || ret > ave + range){
		ret = FRand(ave - range, ave + range);
	}
	return ret;
}

//ラジアンで取得
double Random::FRadRand()
{
	return FRand(-PI, PI);
}
double Random::FRadRand(double deg_min, double deg_max)
{
	return FRand(deg_min * DegToRad, deg_max * DegToRad);
}

//半径rの円上の点を返す
void Random::RandOnCircle(double r, double &x, double &y){
	double randang = FRadRand();
	x = r * cos(randang);
	y = r * sin(randang);
}
//半径rの円上の点を返す　原点からの角度も返す
void Random::RandOnCircle(double r, double &x, double &y, double &ang){
	double randang = FRadRand();
	x = r * cos(randang);
	y = r * sin(randang);
	ang = randang;
}
//半径rの円内部の点を返す
void Random::RandInCircle(double r, double &x, double &y){
	double randang = FRadRand();
	double rr = r * Value();
	x = rr * cos(randang);
	y = rr * sin(randang);
}
//半径rの円内部の点を返す　原点からの角度も返す
void Random::RandInCircle(double r, double &x, double &y, double &ang){
	double randang = FRadRand();
	double rr = r * Value();
	x = rr * cos(randang);
	y = rr * sin(randang);
	ang = randang;
}
//半径rの円上の点を返す
Vector2 Random::RandOnCircle(double r){
	Vector2 temp;
	double randang = FRadRand();
	temp.x = r * cos(randang);
	temp.y = r * sin(randang);
	return temp;
}
//半径rの円上の点を返す
Vector2 Random::RandOnCircle(double r1, double r2){
	Vector2 temp;
	double r = Random::FRand(r1, r2);
	double randang = FRadRand();
	temp.x = r * cos(randang);
	temp.y = r * sin(randang);
	return temp;
}
//半径rの円内部の点を返す
Vector2 Random::RandInCircle(double r){
	Vector2 temp;
	double randang = FRadRand();
	double rr = r * Value();
	temp.x = rr * cos(randang);
	temp.y = rr * sin(randang);
	return temp;
}

Vector2 Random::RandScreenEdge(){
	double marge = 50;
	double p = (double)ScreenHeight / (ScreenWidth + ScreenHeight);

	if (Random::RandBool(p)){
		if (Random::RandBool(0.5)){
			return Vector2(-marge, Random::FRand(ScreenHeight * 0.5));
		}
		else{
			return Vector2(ScreenWidth + marge, Random::FRand(ScreenHeight * 0.5));
		}
	}
	else{
		return Vector2(Random::FRand(ScreenWidth), -marge);
	}
}

Vector2 Random::RandInScreen(){
	return Vector2(Random::FRand(ScreenWidth), Random::FRand(ScreenHeight));
}


//pの確率でtrueを返す
bool Random::RandBool(double p){
	return Random::FRand(1.0) < p;
}

HSV Random::RandHSV(){
	return HSV(Random::FRand(1.0), Random::FRand(1.0), Random::FRand(1.0));
}

namespace Func{

	//2乗
	inline double Sqr(double x)
	{
		return x*x;
	}
	//原点との距離を返す
	double dist(double x, double y){
		return sqrt(x*x + y*y);
	}

	//2点の距離を返す
	double dist(double x1, double y1, double x2, double y2){
		return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}

	//2点の距離の2乗を返す
	double distSqr(double x1, double y1, double x2, double y2){
		return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	}

	//内積計算
	double Dot2D(double Ax, double Ay, double Bx, double By)
	{
		return Ax*Bx + Ay*By;
	}
	//外積計算
	double Cross2D(double Ax, double Ay, double Bx, double By)
	{
		return Ax*By - Bx*Ay;
	}

	//円形同士
	bool Circles(double x1, double y1, double r1, double x2, double y2, double r2)
	{
		return Sqr(x2 - x1) + Sqr(y2 - y1) < Sqr(r2 + r1);
	}
	bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2)
	{
		return Sqr(c2.x - c1.x) + Sqr(c2.y - c1.y) < Sqr(r2 + r1);
	}
	//矩形同士
	bool Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y)
	{
		return a1x < b2x && a1y < b2y && b1x < a2x && b1y < a2y;
	}
	bool Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2)
	{
		return a1.x < b2.x && a1.y < b2.y && b1.x < a2.x && b1.y < a2.y;
	}
	//点と幅のある線 (点の座標、幅のある線の始点・終点)
	bool BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad){
		double x, y, ang, width;
		x = px - line_sx;
		y = py - line_sy;
		ang = atan2(line_ey - line_sy, line_ex - line_sx);
		width = dist(line_sx, line_sy, line_ex, line_ey);

		rotateOnZero(x, y, -ang);

		if (x > 0 && x < width && y > -broad && y < broad){
			return true;
		}
		else{
			return false;
		}
	}

	//点と幅のある線 (点の座標、幅のある線の始点・終点までの距離、角度)
	bool BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad){
		double x, y;
		x = px - line_sx;
		y = py - line_sy;

		rotateOnZero(x, y, -e_ang);

		if (x > 0 && x < e_r && y > -broad && y < broad){
			return true;
		}
		else{
			return false;
		}
	}

	//点と矩形
	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height){
		return abs(px - box_cx) < box_width / 2
			&& abs(py - box_cy) < box_height / 2;
	}

	//点と矩形
	bool BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size){
		return abs(p_pos.x - box_pos.x) < box_size.x / 2
			&& abs(p_pos.y - box_pos.y) < box_size.y / 2;
	}
	//普通の点と矩形
	bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y)
	{
		return  b1x < px  && px < b2x
			&&  b1y < py  && py < b2y;
	}

	//円(半径cr,(cx,cy))の近似正方形と　長方形(左上(rx1,ry1), 右下(rx2, ry2))の当たり判定
	bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2){
		double rectx = (rx1 + rx2) / 2.0;
		double recty = (ry1 + ry2) / 2.0;
		return	cx > rx1 - cr && cy > ry1 - cr &&
			cx < rx2 + cr && cy < ry2 + cr;
	}
	//線分同士(0ならあたってない、0以上はあたってる
	double Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y)
	{
		double c0;
		c0 = Cross2D(b_x - a_x, b_y - a_y, d_x - c_x, d_y - c_y);
		if (c0 == 0.0f)
			return 0.0f;
		double r0, r1;
		r0 = Cross2D(c_x - a_x, c_y - a_y, b_x - a_x, b_y - a_y) / c0;
		r1 = Cross2D(c_x - a_x, c_y - a_y, d_x - c_x, d_y - c_y) / c0;
		if (r0 >= 0.0f && r0 <= 1.0f && r1 >= 0.0f && r1 <= 1.0f)
			return r1;
		else
			return 0.0f;
	}
	//Linesで当たってた場合は位置を計算できる
	Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y)
	{
		Vector2 AB(b_x - a_x, b_y - a_y);
		AB *= lines_result;
		AB.Translate(a_x, a_y);
		return AB;
	}
	//円と線分
	bool CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey)
	{
		if (distSqr(sx, sy, cx, cy) < r*r || distSqr(ex, ey, cx, cy) < r*r){
			return true;
		}
		else {
			double k = ey - sy;
			double l = ex - sx;
			if (!((k*cx - l*cy - k*sx + l*sy)*(k*cx - l*cy - k*sx + l*sy) < r * r * (k*k + l*l))){
				return false;
			}
			if (((sx - cx)*(ex - cx) + (sy - cy)*(ey - cy)) < 0){
				return true;
			}
		}
		return false;
	}


	//ベクトル

	//原点を中心にang分回転
	void rotateOnZero(double &x, double &y, double ang){
		double sx = x - 0;
		double sy = y - 0;
		x = sx * cos(ang) - sy * sin(ang) + 0;
		y = sx * sin(ang) + sy * cos(ang) + 0;
	}

	//ある点(centerx,centery)を中心にang分回転
	void rotateOnPoint(double &x, double &y, double centerx, double centery, double ang){
		double sx = x - centerx;
		double sy = y - centery;
		x = sx * cos(ang) - sy * sin(ang) + centerx;
		y = sx * sin(ang) + sy * cos(ang) + centery;
	}

	//(原点から(sx,sy)への単位ベクトルを求める
	void normalizedVector(double &vx, double &vy, double sx, double sy){
		double rd = atan2(sy, sx);
		vx = cos(rd);
		vy = sin(rd);
	}

	//(sx,sy)から(ex,ey)への単位ベクトルを求める
	void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey){
		double rd = atan2(ey - sy, ex - sx);
		vx = cos(rd);
		vy = sin(rd);
	}

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに代入
	void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
		double rd = atan2(ey - sy, ex - sx);
		resultx = dist * cos(rd);
		resulty = dist * sin(rd);
	}

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
		double rd = atan2(ey - sy, ex - sx);
		resultx += dist * cos(rd);
		resulty += dist * sin(rd);
	}

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	void addVector(double r, double angle, double &resultx, double &resulty){
		resultx += r * cos(angle);
		resulty += r * sin(angle);
	}

	//極座標表現からxy表現に直す
	void polarToXY(double &x, double &y, double r, double ang){
		x = r * cos(ang);
		y = r * sin(ang);
	}

	//角度を計算
	double calAngle(double x, double y){
		return atan2(y, x);
	}

	//角度を計算
	double calAngle(double sx, double sy, double ex, double ey){
		return atan2(ey - sy, ex - sx);
	}


	//グラフ関連

	//3点を通る直線グラフ
	double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end){
		if (t_now < t1){
			return (x1 - x0) * t_now / t1 + x0;
		}
		else{
			return (x2 - x1) * (t_now - t1) / (t_end - t1) + x1;
		}
	}

	//4点を通る直線グラフ
	double graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end){
		if (t_now < t1){
			return (x1 - x0) * t_now / t1 + x0;
		}
		else if (t_now < t2){
			return (x2 - x1) * (t_now - t1) / (t2 - t1) + x1;
		}
		else{
			return (x3 - x2) * (t_now - t2) / (t_end - t2) + x2;
		}
	}

	//ベジェ曲線  p1->p2->p3  0<t<1
	double bzCurve(double p1, double p2, double p3, double t){
		double tp = 1 - t;
		return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
	}

	//ベジェ曲線  p1->p2->p3  nowtime, endtime
	double bzCurve(double p1, double p2, double p3, double nowt, double endt){
		double t = nowt / endt;
		double tp = 1 - t;
		return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
	}

	//アニメーション用・＼／＼／＼／となるグラフ
	int Repeat(int frame, int loop_num)
	{
		--loop_num;
		frame = frame % (loop_num * 2);
		if (frame > loop_num)
			return loop_num * 2 - frame;
		else
			return frame;
	}

	//2次ベジエ曲線を計算する関数
	Vector2 GetBezier2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t)
	{
		Vector2 Result;
		// P = t^2*P0 + 2t(1-t)P1 + (1-t)^2P2
		Result.x = (t*t)*End.x + 2 * t*(1 - t)*Control.x + (1 - t)*(1 - t)*Start.x;
		Result.y = (t*t)*End.y + 2 * t*(1 - t)*Control.y + (1 - t)*(1 - t)*Start.y;
		return Result;
	}

	//2次ベジエ曲線で制御点も通るように引きたい場合の制御点を返す関数
	Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint)
	{
		Vector2 C;
		C.x = (4 * PassPoint.x - Start.x - End.x) / 2.0f;
		C.y = (4 * PassPoint.y - Start.y - End.y) / 2.0f;
		return C;
	}

	//Controlを通る2次ベジエ曲線を計算する関数
	Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t)
	{
		Vector2 C;//Controlを通る2次ベジエ曲線の制御点
		Vector2 Result;
		C.x = (4 * Control.x - Start.x - End.x) / 2.0f;
		C.y = (4 * Control.y - Start.y - End.y) / 2.0f;
		Result.x = (t*t)*End.x + 2 * t*(1 - t)*C.x + (1 - t)*(1 - t)*Start.x;
		Result.y = (t*t)*End.y + 2 * t*(1 - t)*C.y + (1 - t)*(1 - t)*Start.y;
		return Result;
	}

	//3次ベジエ曲線を計算する関数
	Vector2 GetBezier3(const Vector2& Start, const Vector2& ControlPoint1, const Vector2& ControlPoint2, const Vector2& End, float t)
	{
		Vector2 Result;
		Result.x = (t*t*t)*End.x + 3 * t*t*(1 - t)*ControlPoint2.x
			+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.x + (1 - t)*(1 - t)*(1 - t)*Start.x;
		Result.y = (t*t*t)*End.y + 3 * t*t*(1 - t)*ControlPoint2.y
			+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.y + (1 - t)*(1 - t)*(1 - t)*Start.y;
		return Result;
	}
	//便利関数

	//HSVをRGBに換算 直接関数の引数に渡す用
	DWORD GetColorHSV(int h, int s, int v){
		float f;
		int i, p, q, t;
		int rgb[3];

		i = ((int)floor(h / 60.0f)) % 6;
		f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
		p = (int)(v * (1.0f - (s / 255.0f)));
		q = (int)(v * (1.0f - (s / 255.0f) * f));
		t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

		switch (i){
		case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
		case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
		case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
		case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
		case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
		case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
		}

		return GetColor(rgb[0], rgb[1], rgb[2]);
	}


	//HSVでsetdrawbright
	void SetDrawBrightHSV(int h, int s, int v){
		float f;
		int i, p, q, t;
		int rgb[3];

		i = ((int)floor(h / 60.0f)) % 6;
		f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
		p = (int)(v * (1.0f - (s / 255.0f)));
		q = (int)(v * (1.0f - (s / 255.0f) * f));
		t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

		switch (i){
		case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
		case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
		case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
		case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
		case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
		case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
		}

		SetDrawBright(rgb[0], rgb[1], rgb[2]);
	}

	//0xXXXXXXでSetDrawBrightする関数
	void SetDrawBrightInt(int col){
		SetDrawBright(col >> 16, (col >> 8) & (0x00FF), col & 0x0000FF);
	}

	//自分の角度,相手の角度 2角の関係を返す　時計回り側に動いたほうが近ければ1 そうでなければ-1
	int absAngle(double angle1, double angle2){
		if (sin(angle2 - angle1) > 0){
			return 1;
		}
		else{
			return -1;
		}
	}

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  tarxとの差がerange以下でtarx = xにする
	void moveRate(double &x, double tarx, double rate, double eRange)
	{
		x = x * (1 - rate) + tarx * rate;
		if (abs(x - tarx) < eRange){
			x = tarx;
		}
	}
	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	void moveRate(double &x, double &y, double tarx, double tary, double rate, double eRangeDist)
	{
		x = x * (1 - rate) + tarx * rate;
		y = y * (1 - rate) + tary * rate;
		if (dist(x, y, tarx, tary) < eRangeDist){
			x = tarx;
			y = tary;
		}
	}
	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	void moveRate(Vector2 &v2, const Vector2 &tarv2, double rate, double eRangeDist)
	{
		v2.x = v2.x * (1 - rate) + tarv2.x * rate;
		v2.y = v2.y * (1 - rate) + tarv2.y * rate;
		if (dist(v2.x, v2.y, tarv2.x, tarv2.y) < eRangeDist){
			v2 = tarv2;
		}
	}




	//rateとcoolのセットのcoolを更新・boolを返す
	bool coolCount(int &cool){
		if (cool > 0){
			cool--;
			return false;
		}
		else{
			cool = 0;
			return true;
		}
	}

	//基準・振幅・周期(秒)・経過フレームを指定してsinを返す
	double sinSec(double baseVal, double A, double T, double nowFrame){
		return baseVal + A * sin(2 * PI * nowFrame / 60.0 / T);
	}

	//スクリーンの中心を返す
	Vector2 getScreenCenter(){
		return Vector2(ScreenWidth / 2, ScreenHeight / 2);
	}

	//スクリーンからどれだけ外にいるかを計算し、一定以上だったらfalseを返す
	bool isAlivePos(const Vector2 &pos, double length){
		if (pos.x < 0){
			length += -pos.x;
		}
		if (pos.x > ScreenWidth){
			length += pos.x - ScreenWidth;
		}
		if (pos.y < 0){
			length += -pos.y;
		}
		if (pos.y > ScreenHeight){
			length += pos.y - ScreenHeight;
		}
		return length < AliveLength;
	}

	//ランダムな2文字の大文字アルファベットを返す
	std::string randStr(){
		std::string str;
		for (int i = 0; i < 2; i++){
			str += (char)((int)'A' + GetRand(25));
		}
		return str;
	}

	//ランダムなN文字の大文字アルファベットを返す
	std::string randStr(int n){
		std::string str;
		for (int i = 0; i < n; i++){
			str += (char)((int)'A' + GetRand(25));
		}
		return str;
	}


	//リストからランダムな文字列を選んで返す
	//使用例：Func::randStrVec({ "circle32", "lack_rect32" })
	std::string randStrVec(const std::vector<std::string> &strVec){
		int r = Random::Rand(strVec.size() - 1);
		return strVec[r];
	}

	Vector2 getGraphSizeV2(int gHandle){
		int sx;
		int sy;
		GetGraphSize(gHandle, &sx, &sy);
		return Vector2(sx, sy);
	}

	void strReplace(std::string &target, const std::string &oldValue, const std::string &newValue){
		auto beginIter = target.find(oldValue.c_str());
		if (beginIter != std::string::npos){
			auto endIter = beginIter + oldValue.size();
			target.replace(beginIter, endIter, newValue);
		}
	}


	std::string frameToTimeStr(int frame){
		int sec = frame / 60;
		if ((sec % 60) < 10){
			return std::to_string((int)(sec / 60)) +
				":0" +
				std::to_string((int)(sec % 60));
		}
		else{
			return std::to_string((int)(sec / 60)) +
				":" +
				std::to_string((int)(sec % 60));
		}
	}

	void setBackgroundColor0x(int col){
		SetBackgroundColor(col >> 16, (col >> 8) & (0x00FF), col & 0x0000FF);
	}


}//end of namespace Func

