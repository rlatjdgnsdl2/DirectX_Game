#pragma once
#include <Windows.h>

class UEngineWindowsTimer
{
public:
	ENGINEAPI UEngineWindowsTimer();
	ENGINEAPI ~UEngineWindowsTimer();

	UEngineWindowsTimer(const UEngineWindowsTimer& _Other) = delete;
	UEngineWindowsTimer(UEngineWindowsTimer&& _Other) noexcept = delete;
	UEngineWindowsTimer& operator=(const UEngineWindowsTimer& _Other) = delete;
	UEngineWindowsTimer& operator=(UEngineWindowsTimer&& _Other) noexcept = delete;

	ENGINEAPI void TimeCheck();

	ENGINEAPI float GetDeltaTime()
	{
		return fDeltaTime;
	}

	ENGINEAPI double GetDoubleDeltaTime()
	{
		return DeltaTime;
	}

	ENGINEAPI void TimeStart();

	ENGINEAPI float End();

	ENGINEAPI double DEnd();

	ENGINEAPI void SetTimeScale(float _Scale)
	{
		TimeScale = _Scale;
	}

protected:

private:
	LARGE_INTEGER Count = LARGE_INTEGER();
	LARGE_INTEGER PrevTime = LARGE_INTEGER();

	LARGE_INTEGER CurTime = LARGE_INTEGER();

	double TimeCounter = 0.0f;

	double DeltaTime = 0.0;

	float fDeltaTime = 0.0f;

	float TimeScale = 1.0f;
};

