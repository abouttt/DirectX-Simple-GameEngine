#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	: mbInit(false)
	, mStartTimeStamp(0)
	, mFrameTimeStamp(0)
	, mFrameCount(0)
	, mCyclesPerMilliSeconds(0.f)
	, mFrameTime(-1.f)
	, mElapsedTime(0.f)
	, mAverageFPS(0.f)
	, mFPS(0.f)
{
}

float TimeManager::GetElapsedTime()
{
	return mElapsedTime;
}

float TimeManager::GetDeltaTime()
{
	return mFrameTime / 1000.f;
}

float TimeManager::GetFPS()
{
	return mFPS;
}

void TimeManager::init()
{
	if (mbInit)
	{
		return;
	}

	mCyclesPerMilliSeconds = getCyclesPerMilliSeconds();

	mbInit = true;
}

void TimeManager::clear()
{
	mStartTimeStamp = 0;
	mFrameTimeStamp = 0;
	mFrameCount = 0;
	mFrameTime = -1.f;
	mElapsedTime = 0.f;
	mAverageFPS = 0.f;
	mFPS = 0.f;
}

void TimeManager::beginTick()
{
	mFrameTimeStamp = getCurrentTimeStamp();
	if (mFrameCount == 0)
	{
		mStartTimeStamp = mFrameTimeStamp;
	}
}

void TimeManager::endTick()
{
	mFrameCount++;
	INT64 currentTimeStamp = getCurrentTimeStamp();
	INT64 frameCycles = currentTimeStamp - mFrameTimeStamp;
	INT64 elapsedCycles = currentTimeStamp - mStartTimeStamp;
	mFrameTime = frameCycles / mCyclesPerMilliSeconds;
	mElapsedTime = elapsedCycles / mCyclesPerMilliSeconds;
	mFPS = mFrameTime == 0.f ? 0.f : 1000.f / mFrameTime;
	mAverageFPS = mElapsedTime == 0.f ? 0.f : 1000.f / mElapsedTime * mFrameCount;
}

float TimeManager::getCyclesPerMilliSeconds()
{
	LARGE_INTEGER frequency;
	if (!QueryPerformanceFrequency(&frequency))
	{
		return 0.f;
	}

	return static_cast<float>(frequency.QuadPart / 1000.f);
}

long long TimeManager::getCurrentTimeStamp()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return currentTime.QuadPart;
}
