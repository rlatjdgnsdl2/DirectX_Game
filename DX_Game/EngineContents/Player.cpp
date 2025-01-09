#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>

#include "PlayerFuncManager.h"
#include "AnimationManager.h"





APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	{
		std::shared_ptr<class USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->AddZ(static_cast<float>(Z_ORDER::Player));
		PlayerAnimation.SetSpriteRenderer(SpriteRenderer);
	}
	PlayerAnimation.Init();


	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Player");
	Collision->SetScale3D(FVector(40.0f, 60.0f, 1.0f));
	Collision->SetRelativeLocation(FVector::UP * 30.0f);


	PlayerFuncManager = CreateDefaultSubObject<UPlayerFuncManager>();

	
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();
	ChangeAnimation(PAnimation_State::Stand);
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	DeltaTime = _DeltaTime;
	PrevLocation = GetActorLocation();
	CheckKey(_DeltaTime);
	AnimationUpdate(_DeltaTime);
	FVector NowLocation = GetActorLocation();

	if (PrevLocation.Y < NowLocation.Y)
	{
		IsGroundValue = false;
		IsJumpingValue = true;
		IsFallingValue = false;
	}
	else if (PrevLocation.Y > NowLocation.Y)
	{
		IsGroundValue = false;
		IsJumpingValue = false;
		IsFallingValue = true;
	}
}




