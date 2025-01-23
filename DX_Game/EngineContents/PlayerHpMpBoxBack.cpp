#include "PreCompile.h"
#include "PlayerHpMpBoxBack.h"


UPlayerHpMpBoxBack::UPlayerHpMpBoxBack() 
{
	SetTexture("Player_StatusBar_Back.png",true);
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();
	FVector WidgetSize = GetWorldScale3D();
	SetWorldLocation(FVector(-3.0f, -WindowSize.hY() + WidgetSize.hY()+10.0f));
}

UPlayerHpMpBoxBack::~UPlayerHpMpBoxBack() 
{

}
