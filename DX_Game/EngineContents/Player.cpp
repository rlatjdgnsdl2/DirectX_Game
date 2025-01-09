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
	PlayerFuncManager->SetFuncName(VK_LEFT, "VK_LEFT");
	PlayerFuncManager->SetFuncName(VK_RIGHT, "VK_RIGHT");
	PlayerFuncManager->SetFuncName(VK_DOWN, "VK_DOWN");
	PlayerFuncManager->SetFuncName(VK_UP, "VK_UP");
	PlayerFuncManager->SetFuncName('C', "Jump");

	ChanegeAnimation("Stand");
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	DeltaTime = _DeltaTime;
	


}




