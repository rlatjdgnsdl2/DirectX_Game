#include "PreCompile.h"
#include "Player.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "PlayerFuncManager.h"



#include "UIShortKey.h"




APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Player");
	Collision->SetScale3D(FVector(40.0f, 60.0f, 1.0f));
	Collision->SetRelativeLocation(FVector::UP*30.0f);



	SpriteRenderer->AddRelativeLocation(FVector(0.0f, 0.0f, static_cast<float>(Z_ORDER::Player)));
	

	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0,2);
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer->CreateAnimation("Prone", "Player_Prone.png", 0, 0);
	SpriteRenderer->CreateAnimation("UltimateDrive_StartEnd", "Player_UltimateDrive_StartEnd.png", 0, 3);
	SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown", "Player_UltimateDrive_KeyDown.png", 0, 5);
	
	PlayerFuncManager = CreateDefaultSubObject<UPlayerFuncManager>();
	PlayerFuncManager->SetFuncName(VK_LEFT, "Walk_Left");
	PlayerFuncManager->SetFuncName(VK_RIGHT, "Walk_Right");
	PlayerFuncManager->SetFuncName('C', "Jump");
	PlayerFuncManager->SetFuncName('Z', "UltimateDrive");

	SpriteRenderer->ChangeAnimation("Stand");
	
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
	if (UEngineInput::IsDown('Z')) {
		GetWorld()->SpawnActor<UIShortKey>();
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
