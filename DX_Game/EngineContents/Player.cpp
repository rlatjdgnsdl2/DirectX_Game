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
	
	CreateState(Player_State::Stand, std::bind(&APlayer::Stand, this, std::placeholders::_1));
	CreateState(Player_State::Walk, std::bind(&APlayer::Walk, this, std::placeholders::_1));
	CreateState(Player_State::Jump, std::bind(&APlayer::Jump, this, std::placeholders::_1));
	CreateState(Player_State::Prone, std::bind(&APlayer::Prone, this, std::placeholders::_1));
	CreateState(Player_State::Ultimate_Drive, std::bind(&APlayer::Prone, this, std::placeholders::_1));

	ChangeState(Player_State::Stand);
	ChangeAnimation(PAnimation_State::Stand);
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	DeltaTime = _DeltaTime;
	Update(_DeltaTime);
}




