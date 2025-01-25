#include "PreCompile.h"
#include "CQ57.h"
#include "MyGameInstance.h"


ACQ57::ACQ57()
{

	SpriteRenderer->CreateAnimation("Spawn", "Elite_Spawn", 0, 7, 1.0f / 8, false);
	SpriteRenderer->CreateAnimation("KnockBack", "CQ57_KnockBack", 0, 26, 1.0f / 12, false);
	SpriteRenderer->CreateAnimation("PhantomBlow", "CQ57_PhantomBlow", 0, 13, 0.1f, false);

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(250.0f, 150.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-130.0f, 60.0f, 0.0f));
		Collision->SetCollisionStay(std::bind(&ACQ57::KnockBack, this, std::placeholders::_1, std::placeholders::_1));
		Collision->SetActive(false);
		InsertCollision("KnockBack", Collision);
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(300.0f, 150.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-130.0f, 60.0f, 0.0f));
		Collision->SetCollisionStay(std::bind(&ACQ57::PhantomBlow, this, std::placeholders::_1, std::placeholders::_1));
		Collision->SetActive(false);
		InsertCollision("PhantomBlow", Collision);
	}


	FSM.CreateState(0,
		[this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				UEngineRandom Random;
				int Pattern = Random.RandomInt(1, 2);
				FSM.ChangeState(Pattern);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Spawn", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 110.0f, UContentsConst::MONSTER_ZPOS));
		});
	FSM.CreateState(1, std::bind(&ACQ57::UpdateKnockBack, this, std::placeholders::_1), std::bind(&ACQ57::StartKnockBack, this));
	FSM.CreateState(2, std::bind(&ACQ57::UpdatePhantomBlow, this, std::placeholders::_1), std::bind(&ACQ57::StartPhantomBlow, this));
}

ACQ57::~ACQ57()
{
}

void ACQ57::BeginPlay()
{
	AMonster::BeginPlay();
	FSM.ChangeState(0);
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
	UEngineRandom Random;
	int Num = Random.RandomInt(0, 1);
	if (Num == 0)
	{
		Dir = 1;
	}
	else
	{
		Dir = -1;
	}
	SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));
	SetActorLocation(FVector(PlayerPos.X + 200.0f * Dir, 0.0f));
}

void ACQ57::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void ACQ57::StartKnockBack()
{
	SpriteRenderer->ChangeAnimation("KnockBack", true);
	SpriteRenderer->SetRelativeLocation(FVector(60.0f, 110.0f, UContentsConst::MONSTER_ZPOS));
	StartPosX = GetActorLocation().X;
	TargetPosX = StartPosX + 400.0f * -Dir;
}

void ACQ57::UpdateKnockBack(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
	CurIndex = SpriteRenderer->GetCurIndex();
	if (CurIndex >= 17  || CurIndex <= 12)
	{
		return;
	}
	if (CurIndex == 16)
	{
		GetCollision("KnockBack")->SetActive(false);
		return;
	}
	if (CurIndex != PrevIndex)
	{
		if (CurIndex == 13)
		{
			GetCollision("KnockBack")->SetActive(true);
		}
	}
	CurTime += _DeltaTime;
	SetActorLocation(FVector(UEngineMath::Lerp(StartPosX, TargetPosX, UEngineMath::Clamp(CurTime / 0.1f, 0.0f, 1.0f)), 0.0f, 1.0f));
	PrevIndex = CurIndex;
}

void ACQ57::KnockBack(UCollision* _Left, UCollision* _Right)
{
	GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.2f);
	GetCollision("KnockBack")->SetActive(false);
}


void ACQ57::StartPhantomBlow()
{
	SpriteRenderer->ChangeAnimation("PhantomBlow", true);
	SpriteRenderer->SetRelativeLocation(FVector(-120.0f, 110.0f, UContentsConst::MONSTER_ZPOS));
}

void ACQ57::UpdatePhantomBlow(float _DeltaTime)
{

	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
	CurIndex = SpriteRenderer->GetCurIndex();
	if (CurIndex > 7 || CurIndex == 0)
	{
		return;
	}

	if (CurIndex != PrevIndex)
	{
		GetCollision("PhantomBlow")->SetActive(true);
		if (CurIndex == 4)
		{
			GetCollision("PhantomBlow")->SetActive(false);

		}
		PrevIndex = CurIndex;
	}
}

void ACQ57::PhantomBlow(UCollision* _Left, UCollision* _Right)
{
	GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.07f);
	GetCollision("PhantomBlow")->SetActive(false);
}