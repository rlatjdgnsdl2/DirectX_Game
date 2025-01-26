#include "PreCompile.h"
#include "DownChain.h"

ADownChain::ADownChain()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("Chain", "Chain_Effetc", 0, 42, 0.1f, false);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 180.0f, UContentsConst::B_EFFECT_FRONT_ZPOS));

	
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(40.0f, 380.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-150.0f, 250.0f, 0.0f));
		Collision->SetRotation(FVector(0.0f, 0.0f, -45.0f));
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.1f);
				Collisions[0]->SetActive(false);
			});
		Collisions.push_back(Collision);
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(40.0f, 450.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-170.0f, 200.0f, 0.0f));
		Collision->SetRotation(FVector(0.0f, 0.0f, -27.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.1f);
				Collisions[1]->SetActive(false);
			});
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collisions.push_back(Collision);
	}
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(40.0f, 450.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-20.0f, 170.0f, 0.0f));
		Collision->SetRotation(FVector(0.0f, 0.0f, -10.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.1f);
				Collisions[2]->SetActive(false);
			});
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collisions.push_back(Collision);
	}
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(40.0f, 450.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(45.0f, 160.0f, 0.0f));
		Collision->SetRotation(FVector(0.0f, 0.0f, 30.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.1f);
				Collisions[3]->SetActive(false);
			});
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collisions.push_back(Collision);
	}
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(40.0f, 450.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(160.0f, 160.0f, 0.0f));
		Collision->SetRotation(FVector(0.0f, 0.0f, 15.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.1f);
				Collisions[4]->SetActive(false);
			});
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collisions.push_back(Collision);
	}
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(40.0f, 280.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(140.0f, 280.0f, 0.0f));
		Collision->SetRotation(FVector(0.0f, 0.0f, 45.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.1f);
				Collisions[5]->SetActive(false);
			});
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collisions.push_back(Collision);
	}




}

ADownChain::~ADownChain()
{
}

void ADownChain::BeginPlay()
{
	AActor::BeginPlay();
	SpriteRenderer->ChangeAnimation("Chain", true);
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
	SetActorLocation(FVector(PlayerPos.X, 0.0f));

}

void ADownChain::Tick(float _DeltaTime)
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
		case 27:
			for (UMyCollision* iter : Collisions)
			{
				iter->SetActive(true);
			}
			break;
		case 30:
			for (UMyCollision* iter : Collisions)
			{
				iter->SetActive(false);
			}
			break;
		}
		PrevIndex = CurIndex;
	}

}

