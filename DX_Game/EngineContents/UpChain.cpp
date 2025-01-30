#include "PreCompile.h"
#include "UpChain.h"

AUpChain::AUpChain()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("Chain", "Khaliain_Chain_Effect", 0, 12, 0.15f, false);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 80.0f, UContentsConst::M_EFFECT_FRONT_ZPOS));

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("MonsterAttack");
	Collision->SetRelativeScale3D(FVector(100.0f, 100.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	Collision->SetColor(UContentsConst::ATTACK_COLOR);
	Collision->SetActive(false);
	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.1f);
			Collision->SetActive(false);
		});
}

AUpChain::~AUpChain()
{
}

void AUpChain::BeginPlay()
{
	AActor::BeginPlay();
	SpriteRenderer->ChangeAnimation("Chain", true);
}

void AUpChain::Tick(float _DeltaTime)
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
		case 9:
			Collision->SetActive(true);
			break;
		case 10:
			Collision->SetActive(true);
			break;
		case 11:
			Collision->SetActive(true);
			break;
		case 12:
			Collision->SetActive(true);
			break;
		}
		PrevIndex = CurIndex;
	}
}

