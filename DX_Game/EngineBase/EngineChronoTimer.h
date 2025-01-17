#pragma once
#include <chrono>

//	Ό³Έν:
class UEngineChronoTimer
{
public:
	UEngineChronoTimer();
	virtual ~UEngineChronoTimer();
	UEngineChronoTimer(const UEngineChronoTimer& _Other) = delete;
	UEngineChronoTimer(UEngineChronoTimer&& _Other) noexcept = delete;
	UEngineChronoTimer& operator=(const UEngineChronoTimer& _Other) = delete;
	UEngineChronoTimer& operator=(UEngineChronoTimer&& _Other) noexcept = delete;
    void TimeCheck();

    float GetDeltaTime()
    {
        return fDeltaTime;
    }

    double GetDoubleDeltaTime()
    {
        return DeltaTime;
    }

    void TimeStart();

    float End();

    double DEnd();

    void SetTimeScale(float _Scale)
    {
        TimeScale = _Scale;
    }

private:
    std::chrono::high_resolution_clock::time_point PrevTime;
    std::chrono::high_resolution_clock::time_point CurTime;

    double DeltaTime = 0.0;
    float fDeltaTime = 0.0f;
    float TimeScale = 1.0f;


};

