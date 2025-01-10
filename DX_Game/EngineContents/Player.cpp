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

	GetWorld()->LinkCollisionProfile("Player", "FootHold");

	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			if (BoolValue.IsFallingValue) {
				BoolValue.SetGroundTrue();
				GravityAccel = 0.0f;
				this->AddActorLocation(FVector(0.0f, 10.0f, 0.0f));

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
	CheckKey(_DeltaTime);
	Gravity(_DeltaTime);
}


void APlayer::Gravity(float _DeltaTime)
{
	if (!BoolValue.IsGroundValue) {
		GravityAccel += GravityValue * _DeltaTime;
		AddActorLocation(FVector(0.0f, (JumpPoewr - GravityAccel) * _DeltaTime, 0.0f));
		if (GravityAccel > JumpPoewr)
		{
			BoolValue.IsFallingValue = true;
			BoolValue.IsJumpingValue = false;
		}
		else if (GravityAccel < JumpPoewr)
		{
			BoolValue.IsFallingValue = false;
			BoolValue.IsJumpingValue = true;
		}
	}
}




