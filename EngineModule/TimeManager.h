#pragma once

class TimeManager
{
public:
	friend class GameEngine;

public:
	TimeManager();

public:
	float GetElapsedTime();
	float GetDeltaTime();
	float GetFPS();

private:
	void init();
	void clear();
	void beginTick();
	void endTick();
	float getCyclesPerMilliSeconds();
	long long getCurrentTimeStamp();

private:
	bool mbInit;
	long long mStartTimeStamp;
	long long mFrameTimeStamp;
	long mFrameCount;
	float mCyclesPerMilliSeconds;
	float mFrameTime;
	float mElapsedTime;
	float mAverageFPS;
	float mFPS;
};

