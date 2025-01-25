#include "PreCompile.h"
#include "Dunkel_SwordPower.h"




ADunkel_SwordPower::ADunkel_SwordPower()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->AddRelativeLocation(FVector(0.0f, 270.0f));
	SpriteRenderer->SetZ(UContentsConst::P_EFFECT_FRONT_ZPOS);
	SpriteRenderer->CreateAnimation("Effect", "Dunkel_SwordPower_Effect", 0, 7);

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("BossAttack");
	Collision->SetRelativeScale3D(FVector(600.0f, 660.0f, 1.0f));
	Collision->AddRelativeLocation(FVector(0.0f, 270.0f));
	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			if (_Right->GetCollisionProfileName() == "PLAYER")
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(1.5f);
			}
		});

}

ADunkel_SwordPower::~ADunkel_SwordPower()
{

}

void ADunkel_SwordPower::BeginPlay()
{
	AActor::BeginPlay();
	SpriteRenderer->ChangeAnimation("Effect", true);
	SpriteRenderer->SetActive(false);
	Collision->SetActive(false);
	SetActorLocation(StartPos);
	SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));

}

void ADunkel_SwordPower::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	SpawnTime += _DeltaTime;
	if (SpawnTime > (3.0f / 20) * 12)
	{
		SpriteRenderer->SetActive(true);
		Collision->SetActive(true);
		AddActorLocation(FVector(-Dir * 1500.0f * _DeltaTime, 0.0f, 0.0f));

	}
	if (SpawnTime > 5.0f)
	{
		Destroy();
	}

}
