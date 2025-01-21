#include "PreCompile.h"
#include "PillarLight.h"


APillarLight::APillarLight() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("PillarLight", "PillarLight", 0, 30);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 370.0f, 0.0f));

	Collision = CreateDefaultSubObject<UCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("MonsterAttack");
	Collision->SetRelativeScale3D(FVector(250.0f, 500.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(0.0f, 250.0f));


}

APillarLight::~APillarLight() 
{

}

void APillarLight::BeginPlay()
{
	AActor::BeginPlay();
	SpriteRenderer->ChangeAnimation("PillarLight");
}

void APillarLight::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}
