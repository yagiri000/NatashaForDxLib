#include <numeric>
#include <sstream>
#include <iomanip>

#include "GameMgr.h"
#include "ObjectMgr.h"
#include "Button.h"
#include "Func.h"
#include "Draw.h"
#include "MyString.h"



HSV360::HSV360(double h_, double s_, double v_) :
h(h_),
s(s_),
v(v_)
{
};

void HSV360::set(double h_, double s_, double v_){
	h = h_;
	s = s_;
	v = v_;
}

DWORD HSV360::GetRGB(){
	return Func::GetColorHSV(h, s, v);
}


IButton::IButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_) :
pos(pos_),
size(size_),
label(label_),
func(func_),
boxHSV360(Random::Rand(360), 128, 255),
boxAlpha(255),
fontColor(0x000000),
fontName("SegoeUI18"),
isOnMouse(false),
isClicked(false),
isClicking(false),
isClickEnd(false),
isPushing(false)
{
}


void IButton::checkMouse(){
	isOnMouse = Func::BoxPoint(Input::mousePos(), pos, size);
	isClicked = isOnMouse && Input::keyDown(250);
	isClicking = isOnMouse && Input::keyNow(250);
	isClickEnd = isOnMouse && Input::keyUp(250);
	if (isClicked){
		isPushing = true;
	}
	if (Input::keyUp(250)){
		isPushing = false;
	}
}

void IButton::moveColor(){
	boxAlpha = 240;
	if (isOnMouse){
		Func::moveRate(boxHSV360.s, 255, 0.3, 0.5);
	}
	else{
		Func::moveRate(boxHSV360.s, 128, 0.3, 0.5);
	}
}

void IButton::draw(){
	Draw.centerBox(pos, size, boxHSV360.GetRGB(), boxAlpha);
	Draw.centerText(pos + Vector2(0, -10), fontColor, font(fontName), label, 255);
}

void IButton::update(){
	checkMouse();
	moveColor();
}

void IButton::die(){
	//mgr.effect_.add(std::make_shared<BoxBomb>(pos.x, pos.y, size.x, size.y, boxHSV360.GetRGB()));
	Sound::playone("cut00");
	IsDead = true;
}



Label::Label(const Vector2 &pos_, Vector2 size_, std::string label_) :
IButton(pos_, size_, label_, [](){})
{
	boxHSV360.set(210, 128, 255);
}

void Label::update(){
}

ClickButton::ClickButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_) :
IButton(pos_, size_, label_, func_)
{

}

void ClickButton::update(){
	checkMouse();
	moveColor();
	if (isClicked){
		//mgr.effect_.add(std::make_shared<BoxBomb>(pos.x, pos.y, size.x, size.y, boxHSV360.GetRGB()));
		func();
	}
}

void ClickButton::draw(){
	Draw.centerBox(pos, size, boxHSV360.GetRGB(), boxAlpha);
	Draw.centerText(pos + Vector2(0, -10), fontColor, font(fontName), label, 240);
}

ClickingButton::ClickingButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_) :
IButton(pos_, size_, label_, func_)
{

}

void ClickingButton::moveColor(){
	boxAlpha = 0xEE;
	if (isPushing){
		Func::moveRate(boxHSV360.s, 255, 0.5, 0.5);
	}
	else if (isOnMouse){
		Func::moveRate(boxHSV360.s, 200, 0.5, 0.5);
	}
	else{
		Func::moveRate(boxHSV360.s, 128, 0.5, 0.5);
	}
}

void ClickingButton::update(){
	checkMouse();
	moveColor();
	if (isClicked){
		//mgr.effect_.add(std::make_shared<BoxBomb>(pos.x, pos.y, size.x, size.y, boxHSV360.GetRGB()));
	}
	if (isPushing){
		func();
	}
}

void ClickingButton::draw(){
	Draw.centerBox(pos, size, boxHSV360.GetRGB(), boxAlpha);
	Draw.centerText(pos + Vector2(0, -10), fontColor, font(fontName), label, 240);
}

OnOffButton::OnOffButton(const Vector2 &pos_, Vector2 size_, std::string label_, std::function<void(void)> func_) :
IButton(pos_, size_, label_, func_),
isOn(false)
{

}

void OnOffButton::update(){
	checkMouse();
	moveColor();
	if (isClicked){
		isOn = !isOn;
		//mgr.effect_.add(std::make_shared<BoxBomb>(pos.x, pos.y, size.x, size.y, boxHSV360.GetRGB()));
	}
	if (isOn){
		func();
	}

	if (isOn){
		boxHSV360.v = 200 + 50 * sin(Input::eFrame() * 0.3);
	}
	else{
		boxHSV360.v = 255;
	}
}

void OnOffButton::draw(){
	Draw.centerBox(pos, size,
		boxHSV360.GetRGB(), boxAlpha);
	std::string str = label;

	Draw.centerText(pos + Vector2(0, -10), fontColor, font(fontName), str, 255);
}


PlusMinusButton::PlusMinusButton(const Vector2 &pos_, std::string label_, int &i) :
IButton(pos_, Vector2(32, 32), label_, [](){}),
target(i)
{
	click_vec.emplace_back(
		std::make_shared<ClickButton>(pos + Vector2(-40, 0), Vector2(32, 32), "-", [&]()
	{
		i--;
	}));
	click_vec.emplace_back(
		std::make_shared<ClickButton>(pos + Vector2(40, 0), Vector2(32, 32), "+", [&]()
	{
		i++;
	}));

	boxHSV360.set(32, 255, 255);
	boxAlpha = 200;
	for (auto &i : click_vec){
		i->boxHSV360 = boxHSV360;
	}
}

void PlusMinusButton::update(){
	size = Vector2(32, 32);
	click_vec[0]->pos = pos + Vector2(-40, 0);
	click_vec[1]->pos = pos + Vector2(40, 0);
	for (auto &i : click_vec){
		i->update();
	}
}

void PlusMinusButton::draw(){
	for (auto &i : click_vec){
		i->boxAlpha = boxAlpha * 0.7;
		i->draw();
	}
	Draw.centerBox(pos, size, boxHSV360.GetRGB(), boxAlpha);
	Draw.centerText(pos + Vector2(0, -18), fontColor, font(fontName), label, 240);
	Draw.centerText(pos + Vector2(0, -2), fontColor, font(fontName), std::to_string(target), 240);
}


SlideBar::Bar::Bar(const Vector2 &pos_, Vector2 size_) :
pos(pos_),
size(size_),
color(0xFFFFFF),
boxAlpha(255)
{
}

void SlideBar::Bar::draw(){
	Draw.centerBox(pos, size, color, boxAlpha);
}

SlideBar::SlideBar(const Vector2 &pos_, std::string label_, double &val, double minVal_, double maxVal_) :
IButton(pos_, Vector2(128, 26), label_, [](){}),
marge(8),
col_size(size.x - marge, size.y - marge),
bar(pos_, Vector2(col_size.y, col_size.y)),
ref_val(val),
minVal(minVal_),
maxVal(maxVal_),
mouse_pos_x(0)
{
	boxAlpha = 200;
	boxHSV360.set(32, 255, 255);
	fontColor = 0x000000;

	ref_val = minVal;
	mouse_pos_x = -(col_size.x - bar.size.x) / 2;
	update();
}

void SlideBar::checkMouse(){
	isOnMouse = Func::BoxPoint(Input::mousePos(), pos, col_size);
	isClicked = isOnMouse && Input::keyDown(250);
	isClicking = isOnMouse && Input::keyNow(250);
	isClickEnd = isOnMouse && Input::keyUp(250);
	if (isClicked){
		isPushing = true;
	}
	if (Input::keyUp(250)){
		isPushing = false;
	}
}

void SlideBar::update(){
	checkMouse();

	//座標更新
	col_size = Vector2(size.x - marge, size.y - marge);
	bar.pos = pos;
	bar.size = Vector2::one * col_size.y;

	if (isPushing){
		double mouse_x_rate = 0.0;
		mouse_pos_x = Input::mousex() - pos.x;
		mouse_x_rate = mouse_pos_x / (col_size.x - bar.size.x) * 2.0;
		if (abs(mouse_x_rate) > 1.0){
			if (mouse_x_rate > 0.0){
				mouse_x_rate = 1.0;
				mouse_pos_x = (col_size.x - bar.size.x) / 2;
			}
			else{
				mouse_x_rate = -1.0;
				mouse_pos_x = -(col_size.x - bar.size.x) / 2;
			}
		}
		ref_val = (maxVal - minVal) * (mouse_x_rate * 0.5 + 0.5) + minVal;
	}
	else{
	}

	bar.pos = Vector2(pos.x + mouse_pos_x, pos.y);
}


void SlideBar::draw()
{
	Draw.centerBox(pos, size, 0x222222, boxAlpha);
	Draw.box(Vector2(pos.x - col_size.x / 2, pos.y - col_size.y / 2),
		Vector2(pos.x + mouse_pos_x, pos.y + col_size.y / 2), HSV360(32, 255, 255).GetRGB(), boxAlpha);
	Draw.box(Vector2(pos.x + mouse_pos_x, pos.y - col_size.y / 2),
		Vector2(pos.x + col_size.x / 2, pos.y + col_size.y / 2), HSV360(32, 32, 128).GetRGB(), boxAlpha);
	bar.draw();
	std::ostringstream os;
	os << std::fixed << std::setprecision(2) << ref_val;
	std::string str = label + ":" + os.str();
	Draw.centerText(pos + Vector2(0, -10), fontColor, font(fontName), str, 255);
}


SlideBarInt::SlideBarInt(const Vector2 &pos_, std::string label_, int &ref_i_, int minVal_, int maxVal_) :
IButton(pos_, Vector2(128, 26), label_, [](){}),
marge(8),
col_size(size.x - marge, size.y - marge),
bar(pos_, Vector2(col_size.y, col_size.y)),
ref_i(ref_i_),
maxVal(maxVal_),
minVal(minVal_),
mouse_pos_x(0),
mouse_x_rate(0)
{
	boxAlpha = 200;
	boxHSV360.set(32, 255, 255);
	fontColor = 0x000000;
	ref_i = minVal_;
	mouse_x_rate = -1.0;
	mouse_pos_x = -(col_size.x - bar.size.x) / 2;
}

void SlideBarInt::checkMouse(){
	isOnMouse = Func::BoxPoint(Input::mousePos(), pos, col_size);
	isClicked = isOnMouse && Input::keyDown(250);
	isClicking = isOnMouse && Input::keyNow(250);
	isClickEnd = isOnMouse && Input::keyUp(250);
	if (isClicked){
		isPushing = true;
	}
	if (Input::keyUp(250)){
		isPushing = false;
	}
}

void SlideBarInt::update(){
	checkMouse();
	if (isPushing){
		mouse_pos_x = Input::mousex() - pos.x;
		mouse_x_rate = mouse_pos_x / (col_size.x - bar.size.x);
		mouse_x_rate *= 2.0;
		if (abs(mouse_x_rate) > 1.0){
			if (mouse_x_rate > 0.0){
				mouse_x_rate = 1.0;
				mouse_pos_x = (col_size.x - bar.size.x) / 2;
			}
			else{
				mouse_x_rate = -1.0;
				mouse_pos_x = -(col_size.x - bar.size.x) / 2;
			}
		}

		ref_i = std::min<int>((mouse_x_rate * 0.5 + 0.5) * (maxVal - minVal + 1) + minVal, maxVal);
	}

	bar.pos = Vector2(pos.x + mouse_pos_x, pos.y);
}

SlideBarInt::Bar::Bar(const Vector2 &pos_, Vector2 size_) :
pos(pos_),
size(size_),
color(0xFFFFFF),
boxAlpha(255)
{
}

void SlideBarInt::Bar::draw(){
	Draw.centerBox(pos, size, color, boxAlpha);
}

void SlideBarInt::draw(){
	Draw.centerBox(pos, size, 0x222222, boxAlpha);
	Draw.box(Vector2(pos.x - col_size.x / 2, pos.y - col_size.y / 2),
		Vector2(pos.x + mouse_pos_x, pos.y + col_size.y / 2), HSV360(32, 255, 255).GetRGB(), boxAlpha);
	Draw.box(Vector2(pos.x + mouse_pos_x, pos.y - col_size.y / 2),
		Vector2(pos.x + col_size.x / 2, pos.y + col_size.y / 2), HSV360(32, 32, 128).GetRGB(), boxAlpha);
	bar.draw();
	Draw.centerText(pos + Vector2(0, -10), fontColor, font(fontName), (String() + label + ":" + ref_i)(), 255);
}


BoolButton::BoolButton(const Vector2 &pos_, Vector2 size_, std::string label_, bool &flag_) :
IButton(pos_, size_, label_, [](){}),
flag(flag_)
{
}

void BoolButton::update(){
	checkMouse();
	moveColor();
	if (isClicked){
		flag = !flag;
		//mgr.effect_.add(std::make_shared<BoxBomb>(pos.x, pos.y, size.x, size.y, boxHSV360.GetRGB()));
	}
	if (flag){
		func();
	}

	if (flag){
		boxHSV360.v = 200 + 50 * sin(Input::eFrame() * 0.3);
	}
	else{
		boxHSV360.v = 255;
	}
}

void BoolButton::draw(){
	Draw.centerBox(pos, size, boxHSV360.GetRGB(), boxAlpha);
	std::string str = label;

	if (flag){
		str += ":true";
	}
	else{
		str += ":false";
	}
	Draw.centerText(pos + Vector2(0, -10), fontColor, font(fontName), str, 255);
}


ButtonKeeper::ButtonKeeper(const Vector2 &pos_, Vector2 size_, std::string label_) :
IButton(pos_, size_, label_, [](){}),
marge_y(0)
{
	boxHSV360.set(210, 128, 255);
	boxAlpha = 255;
}

void ButtonKeeper::add(std::shared_ptr<IButton> ptr){
	button_vec.emplace_back(ptr);

	elementSize.y = 0;
	for (auto i = button_vec.begin(); i < button_vec.end(); i++){
		elementSize.y += (**i).size.y;
	}
}

void ButtonKeeper::update(){
	checkMouse();

	int nowpos_y = size.y / 2 + pos.y;


	for (auto &i = button_vec.begin(); i < button_vec.end(); i++){
		auto ptr = *i;
		nowpos_y += ptr->size.y / 2 + marge_y;
		ptr->pos.y = nowpos_y;
		ptr->pos.x = pos.x;
		nowpos_y += ptr->size.y / 2;

		ptr->size.x = size.x;
	}

	for (auto &i = button_vec.begin(); i < button_vec.end(); i++){
		(**i).update();
	}
}

void ButtonKeeper::draw(){
	for (auto &i = button_vec.begin(); i < button_vec.end(); i++){
		(**i).draw();
	}
}


Vector2 ButtonAdder::pos(64, 600 - 16);
Vector2 ButtonAdder::vel(0, -32);
Vector2 ButtonAdder::size(128, 26);

ButtonAdder::ButtonAdder(){
}

void ButtonAdder::add(std::shared_ptr<IButton> ptr){
	ptr->pos = pos;
	ptr->size = size;
	obj.button_.add(ptr);
	pos += vel;
}

void ButtonAdder::addDValIntButton(const std::string &valName, int min, int max){
	auto &map = DVal::int_;
	//キーが見つかったら抜ける・無ければボタンとキー追加
	if (map.find(valName) != map.end()){
		return;
	}
	map[valName] = min;
	obj.button_.add(std::make_shared<SlideBarInt>(pos, valName, map[valName], min, max));
	pos += vel;
}

void ButtonAdder::addDValDoubleButton(const std::string &valName, double min, double max){
	auto &map = DVal::double_;
	//キーが見つかったら抜ける・無ければボタンとキー追加
	if (map.find(valName) != map.end()){
		return;
	}
	map[valName] = min;
	obj.button_.add(std::make_shared<SlideBar>(pos, valName, map[valName], min, max));
	pos += vel;
}

void ButtonAdder::addDValBoolButton(const std::string &valName){
	auto &map = DVal::bool_;
	//キーが見つかったら抜ける・無ければボタンとキー追加
	if (map.find(valName) != map.end()){
		return;
	}
	map[valName] = false;
	obj.button_.add(std::make_shared<BoolButton>(pos, size, valName, map[valName]));
	pos += vel;
}