#include "PreCompile.h"
#include "PlayerHpMpBoxFront.h"
#include <EnginePlatform/EngineWindow.h>



UPlayerHpMpBoxFront::UPlayerHpMpBoxFront() 
{
	SetTexture("Player_StatusBar_Front.png",true);
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();
	FVector WidgetSize = GetWorldScale3D();
	SetWorldLocation(FVector( 0.0f,-WindowSize.hY()+WidgetSize.hY()));
}

UPlayerHpMpBoxFront::~UPlayerHpMpBoxFront() 
{

}
