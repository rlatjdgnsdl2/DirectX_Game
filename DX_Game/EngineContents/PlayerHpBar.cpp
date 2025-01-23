#include "PreCompile.h"
#include "PlayerHpBar.h"

#include "MyGameInstance.h"


UPlayerHpBar::UPlayerHpBar()
{
	SetSprite("Player_HpBar");
	SetPivot(FVector(0.0f, 0.5f));
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();
	FVector WidgetSize = GetWorldScale3D();
	SetWorldLocation(FVector(-75.0f, -WindowSize.hY() + WidgetSize.hY() + 35.0f));


}

UPlayerHpBar::~UPlayerHpBar()
{

}

void UPlayerHpBar::Tick(float _DeltaTime)
{
	UImageWidget::Tick(_DeltaTime);
	if (GetGameInstance<MyGameInstance>()->PlayerStatus.bIsHpChange)
	{
		CurTime += _DeltaTime;
		StartPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.PrevHpPercent;
		TargetPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.CurHpPercent;
		BarLerp(StartPercent, TargetPercent, CurTime,GetGameInstance<MyGameInstance>()->PlayerStatus.bIsHpChange);
	}

}


