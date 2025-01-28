#include "PreCompile.h"
#include "MagicSphere.h"

AMagicSphere::AMagicSphere()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("Magic", "Khaliain_MagicSphere_Effect", 0, 7, 0.1f);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 75.0f, UContentsConst::M_EFFECT_FRONT_ZPOS));

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("MonsterAttack");
	Collision->SetRelativeScale3D(FVector(100.0f, 100.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(0.0f, 75.0f, 0.0f));
	Collision->SetColor(UContentsConst::ATTACK_COLOR);
	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.15f);
			Collision->SetActive(false);
		});
}

AMagicSphere::~AMagicSphere()
{
}

void AMagicSphere::BeginPlay()
{
	AActor::BeginPlay();
	SpriteRenderer->ChangeAnimation("Magic", true);
	SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));
	SetActorLocation(FVector(650.0f * Dir, 0.0f));
}

void AMagicSphere::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (Dir == 1.0f)
	{

		if (GetActorLocation().X < -500.0f )
		{
			Destroy();
			return;
		}
	}
	else if (Dir == -1.0f)
	{
		if (GetActorLocation().X > 500.0f)
		{
			Destroy();
			return;
		}
	}

	bool bIsActive = Collision->IsActive();
	if (!bIsActive)
	{
		DamageDelay -= _DeltaTime;
		if (DamageDelay <= 0.0f)
		{
			DamageDelay = 0.5f;
			Collision->SetActive(true);
		}
	}
	AddActorLocation(FVector(100.0f * -Dir * _DeltaTime, 0.0f, 0.0f));

}

