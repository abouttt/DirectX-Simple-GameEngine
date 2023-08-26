#pragma once

class GameObject;
struct Vector3;
struct Quaternion;

class Debug
{
public:
	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;
	~Debug() = delete;

public:
	static void Log(const std::wstring& log);
	static void Log(int num);
	static void Log(long num);
	static void Log(long long num);
	static void Log(unsigned num);
	static void Log(unsigned long num);
	static void Log(unsigned long long num);
	static void Log(float num);
	static void Log(double num);
	static void Log(long double num);
	static void Log(const Vector3& v);
	static void Log(const Quaternion& q);
	static void Log(const GameObject& go);
};
