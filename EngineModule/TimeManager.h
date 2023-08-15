#pragma once

class TimeManager
{
public:
	friend class GameEngine;

public:
	TimeManager();

public:
	float GetElapsedTime() const;
	float GetDeltaTime() const;
	float GetFPS() const;

private:
	void init();
	void clear();
	void beginTick();
	void endTick();
	float getCyclesPerMilliSeconds() const;
	long long getCurrentTimeStamp() const;

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

