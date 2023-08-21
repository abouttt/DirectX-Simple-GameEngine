#include "pch.h"

#include <GameObject.h>
#include <Vector3.h>
#include <Quaternion.h>

#include "Debug.h"

void Debug::Log(const std::wstring& log)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWriten;
	DWORD size = static_cast<DWORD>(wcslen(log.c_str()));
	WriteConsole(handle, log.c_str(), size, &dwBytesWriten, 0);
	WriteConsole(handle, _T("\n"), 1, &dwBytesWriten, 0);
}

void Debug::Log(const Vector3& v)
{
	char str[64];
	std::snprintf(str, sizeof(str), "(%.3f, %.3f, %.3f)", v.X, v.Y, v.Z);
	std::wstring finalLog(str, &str[sizeof(str)]);
	Log(finalLog);
}

void Debug::Log(const Quaternion& q)
{
	char str[64];
	std::snprintf(str, sizeof(str), "(%.3f, %.3f, %.3f, %.3f)", q.X, q.Y, q.Z, q.W);
	std::wstring finalLog(str, &str[sizeof(str)]);
	Log(finalLog);
}

void Debug::Log(const GameObject& go)
{
	char str[64];
	std::snprintf(str, sizeof(str), "GameObject : %ws", go.GetName().c_str());
	std::wstring finalLog(str, &str[sizeof(str)]);
	Log(finalLog);
}
