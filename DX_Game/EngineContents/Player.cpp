
#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>

#include "PlayerFuncManager.h"
#include "AnimationManager.h"

#include "Skill.h"





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

	GetWorld()->LinkCollisionProfile("Player", "FootHold");
	Collision->SetCollisionEnter([this](UCollision* _Left, UCollision* _Right)
		{
			if (LogicValue.IsFallingValue) {
				LogicValue.SetGroundTrue();
				GravityAccel = FVector::ZERO;
				JumpPower = FVector(0.0f, 0.0f, 0.0f);

			}
		});
	Collision->SetCollisionEnd([this](UCollision* _Left, UCollision* _Right)
		{
			LogicValue.SetGround(false);
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
	Gravity(_DeltaTime);
	CheckKey(_DeltaTime);
}


void APlayer::Gravity(float _DeltaTime)
{
	if (!LogicValue.IsGroundValue) {
		GravityAccel += GravityValue * _DeltaTime;
		AddActorLocation((JumpPower - GravityAccel) * _DeltaTime);
		if (GravityAccel.Y > JumpPower.Y)
		{
			LogicValue.IsFallingValue = true;
			LogicValue.IsJumpingValue = false;
		}
		else if (GravityAccel.Y < JumpPower.Y)
		{
			LogicValue.IsFallingValue = false;
			LogicValue.IsJumpingValue = true;
		}
	}
}




