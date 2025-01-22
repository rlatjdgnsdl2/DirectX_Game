#include "PreCompile.h"
#include "PlayerHpBar.h"

#include "MyGameInstance.h"


UPlayerHpBar::UPlayerHpBar()
{
	SetSprite("Player_HpBar");
	SetPivot(FVector(0.0f, 0.5f));
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();
	FVector WidgetSize = GetWorldScale3D();
	SetWorldLocation(FVector(-80.0f, -WindowSize.hY() + WidgetSize.hY() + 35.0f));


}

UPlayerHpBar::~UPlayerHpBar()
{

}

void UPlayerHpBar::Tick(float _DeltaTime)
{
	if (GetGameInstance<MyGameInstance>()->PlayerStatus.bIsHpChange)
	{
		CurTime += _DeltaTime;
		StartHpPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.PrevHpPercent;
		TargetHpPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.CurHpPercent;
		HpBarLerp(StartHpPercent, TargetHpPercent, CurTime);
	}

}

void UPlayerHpBar::HpBarLerp(float _StartPercent, float _EndPercent, float _f)
{
	float LerpHpPercent = UEngineMath::Lerp(StartHpPercent, TargetHpPercent, UEngineMath::Clamp(_f*3.0f, 0.0f, 1.0f));
	SetCuttingSize(0, FVector(LerpHpPercent, 1.0f));
	if (LerpHpPercent == TargetHpPercent) {
		GetGameInstance<MyGameInstance>()->PlayerStatus.bIsHpChange = false;
		CurTime = 0.0f;
	}
}
