#include "PreCompile.h"
#include "Bar.h"
#include "MyGameInstance.h"


UBar::UBar()
{

}

UBar::~UBar()
{

}



void UBar::BarLerp(float _StartPercent, float _EndPercent, float _f, bool& _bIsChange)
{
	bool& bIsChange = _bIsChange;

	float LerpHpPercent = UEngineMath::Lerp(StartPercent, TargetPercent, UEngineMath::Clamp(_f * 3.0f, 0.0f, 1.0f));
	SetCuttingSize(0, FVector(LerpHpPercent, 1.0f));
	if (LerpHpPercent == TargetPercent) {
		bIsChange = false;
		CurTime = 0.0f;
	}





}
