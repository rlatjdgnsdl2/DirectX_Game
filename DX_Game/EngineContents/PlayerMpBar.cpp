#include "PreCompile.h"
#include "PlayerMpBar.h"
#include "MyGameInstance.h"


UPlayerMpBar::UPlayerMpBar() 
{
	SetSprite("Player_MpBar");
	SetPivot(FVector(0.0f, 0.5f));
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();
	FVector WidgetSize = GetWorldScale3D();
	SetWorldLocation(FVector(-75.0f, -WindowSize.hY() + WidgetSize.hY() + 20.0f));
}

UPlayerMpBar::~UPlayerMpBar() 
{

}

void UPlayerMpBar::Tick(float _DeltaTime)
{
	UBar::Tick(_DeltaTime);
	if (GetGameInstance<MyGameInstance>()->PlayerStatus.bIsMpChange)
	{
		CurTime += _DeltaTime;
		StartPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.PrevMpPercent;
		TargetPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.CurMpPercent;
		BarLerp(StartPercent, TargetPercent, CurTime, GetGameInstance<MyGameInstance>()->PlayerStatus.bIsMpChange);
	}
}
