#include "PreCompile.h"
#include "PillarLight.h"
#include "MyCollision.h"
#include "Player.h"

#include "MyGameInstance.h"


APillarLight::APillarLight()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("PillarLight", "PillarLight", 0, 30, 2.0f / 17, false);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 370.0f, 0.0f));

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("MonsterAttack");
	Collision->SetRelativeScale3D(FVector(250.0f, 500.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(0.0f, 250.0f));
	Collision->SetActive(false);
	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.4);
			Collision->SetActive(false);
		});


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
	CollisionSpawnTime += _DeltaTime;

	if (CollisionSpawnTime >= 2.1f)
	{
		if (!bIsCollisionSpawn)
		{
			Collision->SetActive(true);
			bIsCollisionSpawn = true;
		}
	}
	if (CollisionSpawnTime >= 2.4f) {
		Collision->SetActive(false);
	}

	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}

}
