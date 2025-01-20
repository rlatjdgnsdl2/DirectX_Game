#include "PreCompile.h"
#include "Player.h"
#include <EnginePlatform/EngineInput.h>
#include "PlayerFuncManager.h"
#include "LeftKey.h"
#include "RightKey.h"
#include "DownKey.h"
#include "UpKey.h"



APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer.lock()->SetupAttachment(RootComponent);
	SpriteRenderer.lock()->CreateAnimation("Stand", "Player_Stand.png", 0, 2, 1.0f / 3);
	SpriteRenderer.lock()->CreateAnimation("Walk", "Player_Walk.png", 0, 3, 1.0f / 4);
	SpriteRenderer.lock()->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer.lock()->CreateAnimation("Prone", "Player_Prone.png", 0, 0);
	SpriteRenderer.lock()->CreateAnimation("UltimateDrive_KeyDown", "Player_UltimateDrive_KeyDown.png", 0, 5);
	SpriteRenderer.lock()->SetZ(static_cast<float>(Z_ORDER::Player));


	Collision = CreateDefaultSubObject<UCollision>();
	Collision.lock()->SetupAttachment(RootComponent);
	Collision.lock()->SetCollisionProfileName("Player");
	Collision.lock()->SetRelativeScale3D(FVector(30.0f, 60.0f, 1.0f));
	Collision.lock()->SetRelativeLocation(FVector(-10.0f, 30.0f));

	PlayerFuncManager = CreateDefaultSubObject<UPlayerFuncManager>();
	std::shared_ptr<AActor> SharedPlayer(this);
	{
		std::shared_ptr<APlayerFunction> PlayerFunc = GetWorld()->SpawnActor<ALeftKey>();
		PlayerFunc->SetOwner(SharedPlayer);
		DirFunctionMap.insert(std::make_pair("VK_LEFT", PlayerFunc));
	}
	{
		std::shared_ptr<APlayerFunction> PlayerFunc = GetWorld()->SpawnActor<ARightKey>();
		PlayerFunc->SetOwner(SharedPlayer);
		DirFunctionMap.insert(std::make_pair("VK_RIGHT", PlayerFunc));
	}
	{
		std::shared_ptr<APlayerFunction> PlayerFunc = GetWorld()->SpawnActor<ADownKey>();
		PlayerFunc->SetOwner(SharedPlayer);
		DirFunctionMap.insert(std::make_pair("VK_DOWN", PlayerFunc));
	}
	{
		std::shared_ptr<APlayerFunction> PlayerFunc = GetWorld()->SpawnActor<AUpKey>();
		PlayerFunc->SetOwner(SharedPlayer);
		DirFunctionMap.insert(std::make_pair("VK_UP", PlayerFunc));
	}
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
	CheckKey(_DeltaTime);
	MoveUpdate(_DeltaTime);
}


void APlayer::Gravity(float _DeltaTime)
{
	if (!PlayerLogic.bIsGround) {
		GravityAccel += UContentsConst::Gravity * _DeltaTime;

		AddActorLocation(FVector(0.0f, -GravityAccel * _DeltaTime,0.0f));
		if (GravityAccel > Velocity.Y)
		{
			PlayerLogic.bIsFalling = true;
			PlayerLogic.bIsJumping = false;
		}
		else if (GravityAccel < Velocity.Y)
		{
			PlayerLogic.bIsFalling = false;
			PlayerLogic.bIsJumping = true;
		}
	}
}

void APlayer::MoveUpdate(float _DeltaTime)
{
	Gravity(_DeltaTime);
	AddActorLocation(Velocity * _DeltaTime);
}










