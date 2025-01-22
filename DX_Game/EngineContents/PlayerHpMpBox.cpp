#include "PreCompile.h"
#include "PlayerHpMpBox.h"
#include <EnginePlatform/EngineWindow.h>



UPlayerHpMpBox::UPlayerHpMpBox() 
{
	SetTexture("Player_StatusBar01.png",true);
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();
	FVector WidgetSize = GetWorldScale3D();
	SetWorldLocation(FVector( 0.0f,-WindowSize.hY()+WidgetSize.hY()));
}

UPlayerHpMpBox::~UPlayerHpMpBox() 
{

}
