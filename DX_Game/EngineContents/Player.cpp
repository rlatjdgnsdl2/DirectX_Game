#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include "PlayerFuncManager.h"




APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->AddRelativeLocation(FVector(0.0f, 0.0f, static_cast<float>(Z_ORDER::Player)));
	

	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0,2,0.5f/3);
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3, 0.5/4);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer->ChangeAnimation("Stand");
	
	

	TestRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TestRenderer->SetupAttachment(RootComponent);
	TestRenderer->AddRelativeLocation(FVector(-130.0f, -150.0f, static_cast<float>(Z_ORDER::Skill)));
	TestRenderer->CreateAnimation("Test", "Ultimate_Drive", 0, 5, 0.5f/6);
	TestRenderer->ChangeAnimation("Test");
	

	PlayerFuncManager = CreateDefaultSubObject<UPlayerFuncManager>();
	PlayerFuncManager->SetFuncName(VK_LEFT, "Walk_Left");
	PlayerFuncManager->SetFuncName(VK_RIGHT, "Walk_Right");
	
}

APlayer::~APlayer()
{

}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	DeltaTime = _DeltaTime;

	if (UEngineInput::IsDown(VK_LEFT)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_LEFT)).Down();
		
	}
	if (UEngineInput::IsPress(VK_LEFT)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_LEFT)).Press();
		
	}
	if (UEngineInput::IsDown(VK_RIGHT)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_RIGHT)).Down();
		
	}
	if (UEngineInput::IsPress(VK_RIGHT)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_RIGHT)).Press();
		
	}

	if (UEngineInput::IsDown('C')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('C')).Down();
		
	}

	


	if (UEngineInput::IsPress('W')) {
		GetWorld()->GetMainCamera()->AddRelativeLocation(FVector(0.0f,500.0f * _DeltaTime,0.0f));
	}
	if (UEngineInput::IsPress('A')) {
		GetWorld()->GetMainCamera()->AddRelativeLocation(FVector(-500.0f * _DeltaTime, 0.0f, 0.0f));
	}
	if (UEngineInput::IsPress('S')) {
		GetWorld()->GetMainCamera()->AddRelativeLocation(FVector(0.0f , -500.0f * _DeltaTime, 0.0f));
	}
	if (UEngineInput::IsPress('D')) {
		GetWorld()->GetMainCamera()->AddRelativeLocation(FVector(500.0f * _DeltaTime, 0.0f, 0.0f));
	}





}
