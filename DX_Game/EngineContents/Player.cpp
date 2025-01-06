#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ShortKeyComponent.h"



APlayer::APlayer()
{
	ShortKeyComponent = CreateDefaultSubObject<UShortKeyComponent>();
	ShortKeyComponent->RegisterShortKey('A', "MoveLeft");
	ShortKeyComponent->RegisterShortKey('D', "MoveRight");
	

	
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;
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
	

	if (UEngineInput::IsDown('A'))
	{
		ShortKeyComponent->RegisterShortKey('A', "MoveRight");
		

		//SpriteRenderer->ChangeAnimation("Walk");
		//SetActorRelativeScale3D(FVector{ 1.0f,1.0f,1.0f });
		//AddRelativeLocation(FVector{ -10.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('C'))
	{
		//SpriteRenderer->ChangeAnimation("Jump");
	}
	
	if (UEngineInput::IsPress('D'))
	{
		//SetActorRelativeScale3D(FVector{ -1.0f,1.0f,1.0f });
		//AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	if (UEngineInput::IsPress('W'))
	{
		//AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		//AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}
}
