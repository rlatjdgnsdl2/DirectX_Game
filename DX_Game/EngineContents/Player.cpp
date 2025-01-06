#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>





APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);


	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0,2,0.33f);
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3, 0.25f);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer->ChangeAnimation("Stand");
}

APlayer::~APlayer()
{

}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	DeltaTime = _DeltaTime;

	/*if (UEngineInput::IsDown(VK_LEFT)) {
		PlayerFuncManager.get()->FindFunc(PlayerFuncManager->FindFuncName(VK_LEFT)).DownEvent();
		return;
	}
	if (UEngineInput::IsPress(VK_LEFT)) {
		PlayerFuncManager.get()->FindFunc(PlayerFuncManager->FindFuncName(VK_LEFT)).PressEvent();
		return;
	}*/
}
