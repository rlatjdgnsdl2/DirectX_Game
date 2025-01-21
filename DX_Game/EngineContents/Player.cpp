#include "PreCompile.h"
#include "Player.h"


#include "PlayerFuncManager.h"
#include "Job_Phantom.h"
#include "LeftKey.h"
#include "RightKey.h"
#include "DownKey.h"
#include "UpKey.h"
#include "DamageSkinActor.h"



APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	//Sprite
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0, 2, 1.0f / 3);
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3, 1.0f / 4);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer->CreateAnimation("Prone", "Player_Prone.png", 0, 0);
	SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown", "Player_UltimateDrive_KeyDown.png", 0, 5);
	SpriteRenderer->SetZ(static_cast<float>(Z_ORDER::Player));

	//Collision
	Collision = CreateDefaultSubObject<UCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Player");
	Collision->SetRelativeScale3D(FVector(30.0f, 60.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-10.0f, 30.0f));

	Job = CreateDefaultSubObject<UJob_Phantom>().get();
	PlayerFuncManager = CreateDefaultSubObject<UPlayerFuncManager>().get();
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();	
	//Dir
	{
		std::shared_ptr<APlayerFunction> PlayerFunc = GetWorld()->SpawnActor<ALeftKey>();
		PlayerFunc->SetOwner(this);
		DirFunctionMap.insert(std::make_pair("VK_LEFT", PlayerFunc.get()));
	}
	{
		std::shared_ptr<APlayerFunction> PlayerFunc = GetWorld()->SpawnActor<ARightKey>();
		PlayerFunc->SetOwner(this);
		DirFunctionMap.insert(std::make_pair("VK_RIGHT", PlayerFunc.get()));
	}
	{
		std::shared_ptr<APlayerFunction> PlayerFunc = GetWorld()->SpawnActor<ADownKey>();
		PlayerFunc->SetOwner(this);
		DirFunctionMap.insert(std::make_pair("VK_DOWN", PlayerFunc.get()));
	}
	{
		std::shared_ptr<APlayerFunction> PlayerFunc = GetWorld()->SpawnActor<AUpKey>();
		PlayerFunc->SetOwner(this);
		DirFunctionMap.insert(std::make_pair("VK_UP", PlayerFunc.get()));
	}
	
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	CheckKey(_DeltaTime);
	MoveUpdate(_DeltaTime);
	if (UEngineInput::IsDown('R'))
	{
		GetWorld()->SpawnActor<ADamageSkinActor>()->SetDamage(1234567890213123123);
	}

	UEngineDebug::OutPutString(std::to_string(1 / _DeltaTime));
}


void APlayer::Gravity(float _DeltaTime)
{
	if (!PlayerLogic.bIsGround) {
		PlayerLogic.GravityAccel += UContentsPhysicsConst::GravityAcc * _DeltaTime;

		AddActorLocation(FVector(0.0f, -PlayerLogic.GravityAccel * _DeltaTime,0.0f));
		if (PlayerLogic.GravityAccel > PlayerLogic.Velocity.Y)
		{
			PlayerLogic.bIsFalling = true;
			PlayerLogic.bIsJumping = false;
		}
		else if (PlayerLogic.GravityAccel < PlayerLogic.Velocity.Y)
		{
			PlayerLogic.bIsFalling = false;
			PlayerLogic.bIsJumping = true;
		}
	}
}

void APlayer::MoveUpdate(float _DeltaTime)
{
	Gravity(_DeltaTime);
	AddActorLocation(PlayerLogic.Velocity * _DeltaTime);
}










