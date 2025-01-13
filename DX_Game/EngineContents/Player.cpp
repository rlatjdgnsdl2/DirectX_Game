
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
	Collision->SetScale3D(FVector(30.0f, 60.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-10.0f, 30.0f));

	GetWorld()->LinkCollisionProfile("Player", "FootHold");
	Collision->SetCollisionEnter([this](UCollision* _Left, UCollision* _Right)
		{
			if (LogicValue.IsFallingValue) {
				LogicValue.SetGroundTrue();
				float FootHoldTop = _Right->GetTransformRef().ZAxisWorldCenterTop();
				float PlayerBottom = _Left->GetTransformRef().ZAxisWorldCenterBottom();
				AddActorLocation(FVector(0.0f, FootHoldTop - PlayerBottom, 0.0f));
				GravityAccel = 0.0f;
				Velocity.X = 0.0f;
				Velocity.Y = 0.0f;
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
	MoveUpdate(_DeltaTime);
	CheckKey(_DeltaTime);
}


void APlayer::Gravity(float _DeltaTime) 
{
	if (!LogicValue.IsGroundValue) {
		GravityAccel += GravityValue * _DeltaTime;
		AddActorLocation(FVector(0.0f,- GravityAccel * _DeltaTime));
		if (GravityAccel > Velocity.Y)
		{
			LogicValue.IsFallingValue = true;
			LogicValue.IsJumpingValue = false;
		}
		else if (GravityAccel < Velocity.Y)
		{
			LogicValue.IsFallingValue = false;
			LogicValue.IsJumpingValue = true;
		}
	}
}

void APlayer::MoveUpdate(float _DeltaTime)
{
	Gravity(_DeltaTime);
	AddActorLocation(Velocity * _DeltaTime);
}








