#include "PreCompile.h"
#include "PlayerHpBarEffect.h"


UPlayerHpBarEffect::UPlayerHpBarEffect()
{
	CreateAnimation("HpBar_Effect", "Player_HpBar", 1, 6);
	SetAnimationPivot("HpBar_Effect", FVector(0.0f, 0.5f));
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();
	FVector WidgetSize = GetWorldScale3D();
	SetWorldLocation(FVector(-76.0f, -WindowSize.hY() + WidgetSize.hY() + 35.0f));
}

UPlayerHpBarEffect::~UPlayerHpBarEffect()
{

}

void UPlayerHpBarEffect::Tick(float _DeltaTime)
{
	UBar::Tick(_DeltaTime);
	if (GetGameInstance<MyGameInstance>()->PlayerStatus.bIsHpChange)
	{
		CurTime += _DeltaTime;
		StartPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.PrevHpPercent;
		TargetPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.CurHpPercent;
		BarLerp(StartPercent, TargetPercent, CurTime, GetGameInstance<MyGameInstance>()->PlayerStatus.bIsHpChange);
		ChangeAnimation("HpBar_Effect");
	}
}

void UPlayerHpBarEffect::BarLerp(float _StartPercent, float _EndPercent, float _f, bool& _bIsChange)
{
	bool& bIsChange = _bIsChange;
	float LerpHpPercent = UEngineMath::Lerp(StartPercent, TargetPercent, UEngineMath::Clamp(_f * 3.0f, 0.0f, 1.0f));
	SetAnimationCuttingSize("HpBar_Effect", FVector(LerpHpPercent, 1.0f));
}
