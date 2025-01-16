
#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>

#include "PlayerFuncManager.h"

APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0, 2, 1.0f / 3);
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3, 1.0f / 4);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer->CreateAnimation("Prone", "Player_Prone.png", 0, 0);
	SpriteRenderer->SetZ(static_cast<float>(Z_ORDER::Player));

	SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown", "Player_UltimateDrive_KeyDown.png", 0, 5);

	AnimaionFSM.CreateState(PAnimation_State::Stand, nullptr,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Stand");
		});

	AnimaionFSM.CreateState(PAnimation_State::Walk, nullptr,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Walk");
		});

	AnimaionFSM.CreateState(PAnimation_State::Jump, nullptr,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Jump");
		});

	AnimaionFSM.CreateState(PAnimation_State::Prone, nullptr,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Prone");
		});

	AnimaionFSM.CreateState(PAnimation_State::Ultimate_Drive, nullptr,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("UltimateDrive_KeyDown");
		});
	InitSkill();

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Player");
	Collision->SetRelativeScale3D(FVector(30.0f, 60.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-10.0f, 30.0f));

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
	MainCamera = GetWorld()->GetMainCamera().get();
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (UEngineInput::IsPress(VK_NUMPAD4)) {
		MainCamera->AddActorLocation(FVector(-100.0f, 0.0f));
	}
	if (UEngineInput::IsPress(VK_NUMPAD6)) {
		MainCamera->AddActorLocation(FVector(100.0f, 0.0f));
	}
	if (UEngineInput::IsPress(VK_NUMPAD8)) {
		MainCamera->AddActorLocation(FVector(0.0f, 100.0f));
	}
	if (UEngineInput::IsPress(VK_NUMPAD2)) {
		MainCamera->AddActorLocation(FVector(0.0f, -100.0f));
	}

	CheckKey(_DeltaTime);
	MoveUpdate(_DeltaTime);
	MoveCamera(_DeltaTime);
}


void APlayer::Gravity(float _DeltaTime)
{
	if (!LogicValue.IsGroundValue) {
		GravityAccel += UContentsConst::Gravity * _DeltaTime;

		AddActorLocation(FVector(0.0f, -GravityAccel * _DeltaTime,0.0f));
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

void APlayer::MoveCamera(float _DeltaTime)
{
	MainCamera->SetActorLocation(GetActorLocation());
}








