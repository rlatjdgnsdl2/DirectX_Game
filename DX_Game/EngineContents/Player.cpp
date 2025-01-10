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
	InitSkill();

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Player");
	Collision->SetScale3D(FVector(40.0f, 60.0f, 1.0f));
	Collision->SetRelativeLocation(FVector::UP * 30.0f);

	GetWorld()->LinkCollisionProfile("Player","FootHold");

	Collision->SetCollisionEnter([this](UCollision* _Left, UCollision* _Right) 
		{
			if (IsFalling()) {
				SetGround(true);
				SetJump(false);
				SetFalling(false);
			}
		});


	PlayerFuncManager = CreateDefaultSubObject<UPlayerFuncManager>();
}

APlayer::~APlayer()
{
	SkillMap.clear();
	PlayerFuncManager = nullptr;
	Collision = nullptr;
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
	Gravity(_DeltaTime);
	CheckKey(_DeltaTime);
	FVector NowLocation = GetActorLocation();

	if (PrevLocation.Y < NowLocation.Y)
	{
		BoolValue.IsGroundValue = false;
		BoolValue.IsJumpingValue = true;
		BoolValue.IsFallingValue = false;
	}
	else if (PrevLocation.Y > NowLocation.Y)
	{
		BoolValue.IsGroundValue = false;
		BoolValue.IsJumpingValue = false;
		BoolValue.IsFallingValue = true;
	}
}


void APlayer::Gravity(float _DeltaTime)
{
	if (!IsGround())
	{
		AddActorLocation(GravityForce * _DeltaTime);
		GravityForce += FVector::DOWN * _DeltaTime * 500.0f;
	}
	else {
		GravityForce = FVector::ZERO;
	}

}




