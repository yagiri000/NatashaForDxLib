#include "MyString.h"
#include <sstream>
#include <iomanip>

//¬”“_ˆÈ‰º‚ÌŒ…”
const int PlaceAfterTheDecimalPoint = 0;

std::string String::operator()(){
	return str;
}

const char* String::c_str(){
	return str.c_str();
}

String::String(){
}

String::String(const std::string &str_) :
str(str_)
{
}

String::String(const char* a) :
str(std::string(a))
{
}
String::String(const int a) :
str(std::to_string(a))
{
}
String::String(const float a)
{
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << a;
	str = os.str();
}
String::String(const double a)
{
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << a;
	str = os.str();
}
String::String(const Vector2 &v2){
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << "(" << v2.x << "," << v2.y << ")";
	str = os.str();
}


String& String::operator+=(const String &str_){
	str += str_.str;
	return *this;
}
String& String::operator+=(const std::string &str_){
	str += str_;
	return *this;
}
String& String::operator+=(const char* a){
	str += std::string(a);
	return *this;
}
String& String::operator+=(const int a){
	str += std::to_string(a);
	return *this;
}
String& String::operator+=(const float a){
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << a;
	str += os.str();
	return *this;
}
String& String::operator+=(const double a){
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << a;
	str += os.str();
	return *this;
}
String& String::operator+=(const Vector2 &v2){
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << "(" << v2.x << "," << v2.y << ")";
	str += os.str();
	return *this;
}



String String::operator+(const String &str_) const{
	String ret(str);
	ret += str_;
	return ret;
}
String String::operator+(const std::string &str_) const{
	String ret(str);
	ret += str_;
	return ret;
}
String String::operator+(const char* a) const{
	String ret(str);
	ret += std::string(a);
	return ret;
}
String String::operator+(const int a) const{
	String ret(str);
	ret += std::to_string(a);
	return ret;
}
String String::operator+(const float a) const{
	String ret(str);
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << a;
	ret += os.str();
	return ret;
}
String String::operator+(const double a) const{
	String ret(str);
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << a;
	ret += os.str();
	return ret;
}
String String::operator+(const Vector2 &v2) const{
	String ret(str);
	std::ostringstream os;
	os << std::fixed << std::setprecision(PlaceAfterTheDecimalPoint) << "(" << v2.x << "," << v2.y << ")";
	ret += os.str();
	return ret;
}