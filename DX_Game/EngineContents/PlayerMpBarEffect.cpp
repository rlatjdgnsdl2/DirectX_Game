#include "PreCompile.h"
#include "PlayerMpBarEffect.h"


UPlayerMpBarEffect::UPlayerMpBarEffect()
{
	CreateAnimation("MpBar_Effect", "Player_MpBar", 1, 6);
	SetAnimationPivot("MpBar_Effect", FVector(0.0f, 0.5f));
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();
	FVector WidgetSize = GetWorldScale3D();
	SetWorldLocation(FVector(-75.0f, -WindowSize.hY() + WidgetSize.hY() + 20.0f));
}

UPlayerMpBarEffect::~UPlayerMpBarEffect()
{

}

void UPlayerMpBarEffect::Tick(float _DeltaTime)
{
	UBar::Tick(_DeltaTime);
	if (GetGameInstance<MyGameInstance>()->PlayerStatus.bIsMpChange)
	{
		CurTime += _DeltaTime;
		StartPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.PrevMpPercent;
		TargetPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.CurMpPercent;
		BarLerp(StartPercent, TargetPercent, CurTime, GetGameInstance<MyGameInstance>()->PlayerStatus.bIsMpChange);
		ChangeAnimation("MpBar_Effect");
	}
}

void UPlayerMpBarEffect::BarLerp(float _StartPercent, float _EndPercent, float _f, bool& _bIsChange)
{
	bool& bIsChange = _bIsChange;
	float LerpHpPercent = UEngineMath::Lerp(StartPercent, TargetPercent, UEngineMath::Clamp(_f * 3.0f, 0.0f, 1.0f));
	SetAnimationCuttingSize("MpBar_Effect", FVector(LerpHpPercent, 1.0f));
}
