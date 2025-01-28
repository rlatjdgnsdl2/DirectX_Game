#include "PreCompile.h"
#include "Sniping.h"

ASniping::ASniping()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("Sniping", "Jurai_Sniping_Effect", 0, 2, 0.1f);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 30.0f, UContentsConst::M_EFFECT_FRONT_ZPOS));

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("MonsterAttack");
	Collision->SetRelativeScale3D(FVector(150.0f, 40.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-20.0f, 30.0f));
	Collision->SetColor(UContentsConst::ATTACK_COLOR);
	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.6f);
			Destroy();
			return;
		});

}

ASniping::~ASniping()
{
}

void ASniping::BeginPlay()
{
	AActor::BeginPlay();
	SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));
	SpriteRenderer->ChangeAnimation("Sniping");
}

void ASniping::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(FVector(700.0f * -Dir * _DeltaTime,0.0f));

	if (GetActorLocation().X < -1000.0f || GetActorLocation().X > 1000.0f)
	{
		Destroy();
	}
}

