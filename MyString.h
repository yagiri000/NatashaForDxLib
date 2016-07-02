//--------------------------------------
//Developing Code "Natasha"
//by yagiri
//--------------------------------------
#pragma once
#include <string>
#include "Vector2.h"

class String{
private:
	std::string str;
public:
	std::string operator()();
	const char* c_str();

	String();
	String(const std::string &str_);
	String(const char* a);
	String(const int a);
	String(const float a);
	String(const double a);
	String(const Vector2 &v2);

	String& operator+=(const String &str);
	String& operator+=(const std::string &str);
	String& operator+=(const char* a);
	String& operator+=(const int a);
	String& operator+=(const float a);
	String& operator+=(const double a);
	String& operator+=(const Vector2 &v2);

	String operator+(const String &str) const;
	String operator+(const std::string &str) const;
	String operator+(const char* a) const;
	String operator+(const int a) const;
	String operator+(const float a) const;
	String operator+(const double a) const;
	String operator+(const Vector2 &v2) const;
};
