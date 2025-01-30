#include "PreCompile.h"
#include "Shot.h"

AShot::AShot()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("Shot", "Freyd_HeadShoot_Effect", 0, 9, 0.15f, false);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 50.0f, UContentsConst::M_EFFECT_FRONT_ZPOS));

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("MonsterAttack");
	Collision->SetRelativeScale3D(FVector(100.0f, 100.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	Collision->SetColor(UContentsConst::ATTACK_COLOR);
	Collision->SetActive(false);
	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.3f);
			Collision->SetActive(false);
		});

}

AShot::~AShot()
{

}

void AShot::BeginPlay()
{
	AActor::BeginPlay();
	SpriteRenderer->ChangeAnimation("Shot", true);
}

void AShot::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
	CurIndex = SpriteRenderer->GetCurIndex();
	if (PrevIndex != CurIndex)
	{
		switch (CurIndex)
		{
		case 8:
			Collision->SetActive(true);
			break;
		}
		PrevIndex = CurIndex;
	}
}





