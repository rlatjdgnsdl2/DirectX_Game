#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ShortKeyComponent.h"



APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	ShortKeyComponent = CreateDefaultSubObject<UShortKeyComponent>();
	ShortKeyComponent->RegisterShortKey('A', "MoveLeft");
	ShortKeyComponent->RegisterShortKey('D', "MoveRight");
	
	

	
	
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);

	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0,2,0.33f);
	SpriteRenderer->ChangeAnimation("Stand");
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3, 0.25f);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);

}

APlayer::~APlayer()
{

}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	

	
}
