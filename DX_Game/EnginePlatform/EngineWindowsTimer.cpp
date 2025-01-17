#include "PreCompile.h"
#include "EngineWindowsTimer.h"

UEngineWindowsTimer::UEngineWindowsTimer()
{
	// ���� 1�ʿ� �󸶸� ���� �ִ� �ֿ���.
	QueryPerformanceFrequency(&Count);

	// ������ ������ �ϱ� ���ؼ� 8����Ʈ 
	TimeCounter = static_cast<double>(Count.QuadPart);

	// ������� �̸�ŭ �����
	QueryPerformanceCounter(&PrevTime);
	QueryPerformanceCounter(&CurTime);

	int a = 0;
}

UEngineWindowsTimer::~UEngineWindowsTimer()
{
}

void UEngineWindowsTimer::TimeStart()
{
	QueryPerformanceCounter(&PrevTime);
}

float UEngineWindowsTimer::End()
{
	TimeCheck();
	return GetDeltaTime();
}

double UEngineWindowsTimer::DEnd()
{
	TimeCheck();
	return GetDoubleDeltaTime();
}

void UEngineWindowsTimer::TimeCheck()
{
	// QueryPerformanceCounter(&PrevTime); ������ ����� �ð��� �������� ���̴�.

	QueryPerformanceCounter(&CurTime);

	// ���̰����� ���ɴϴ�.
	double Tick = static_cast<double>(CurTime.QuadPart - PrevTime.QuadPart);
	DeltaTime = Tick / TimeCounter * TimeScale;
	fDeltaTime = static_cast<float>(DeltaTime);
	PrevTime.QuadPart = CurTime.QuadPart;
}
