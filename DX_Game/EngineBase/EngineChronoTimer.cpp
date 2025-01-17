#include "PreCompile.h"
#include "EngineChronoTimer.h"



UEngineChronoTimer::UEngineChronoTimer()
{
    PrevTime = std::chrono::high_resolution_clock::now();
    CurTime = PrevTime;
}

UEngineChronoTimer::~UEngineChronoTimer()
{
}

void UEngineChronoTimer::TimeStart()
{
    PrevTime = std::chrono::high_resolution_clock::now();
}

float UEngineChronoTimer::End()
{
    TimeCheck();
    return GetDeltaTime();
}

double UEngineChronoTimer::DEnd()
{
    TimeCheck();
    return GetDoubleDeltaTime();
}

void UEngineChronoTimer::TimeCheck()
{
    CurTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> Elapsed = CurTime - PrevTime;

    DeltaTime = Elapsed.count() * TimeScale; // 초 단위로 경과 시간 계산
    fDeltaTime = static_cast<float>(DeltaTime);
    PrevTime = CurTime;
}