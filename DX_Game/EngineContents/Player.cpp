#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>


APlayer::APlayer() 
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PlayerRenderer->CreateAnimation("Idle", "Player_Walk", 0,2 , 0.2f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}
	PlayerRenderer->ChangeAnimation("Idle");
	PlayerRenderer->SetupAttachment(RootComponent);

}

APlayer::~APlayer() 
{

}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsPress('=')) {
		AddActorRotation(FVector(30,30));
	}
}
