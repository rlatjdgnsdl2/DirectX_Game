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
	StartPosX = GetActorLocation().X;
	TargetPosX = StartPosX + 400.0f*-Dir;
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
}

void ACQ57::UpdateKnockBack(float _DeltaTime)
{
	
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
	KnockBackCollisionSpawnTime -= _DeltaTime;
	if (!bIsKnockBackCollisionSpawn)
	{
		if (KnockBackCollisionSpawnTime < 0.0f)
		{
			GetCollision("KnockBack")->SetActive(true);
			bIsKnockBackCollisionSpawn = true;
		}
	}
	else 
	{
		CurTime += _DeltaTime;
		SetActorLocation(FVector(UEngineMath::Lerp(StartPosX, TargetPosX, UEngineMath::Clamp(CurTime*5,0.0f,1.0f)), 0.0f,1.0f));
	}
	
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
	if (PhantomBlowCount > 6)
	{
		return;
	}

	PhantomBlowCollisionSpawnTime -= _DeltaTime;
	if (!bIsPhantomBlowCollisionSpawn)
	{
		if (PhantomBlowCollisionSpawnTime < 0.0f)
		{
			GetCollision("PhantomBlow")->SetActive(true);
			bIsPhantomBlowCollisionSpawn = true;
			PhantomBlowCount++;
			if (PhantomBlowCount == 3)
			{
				PhantomBlowCollisionSpawnTime = 0.2f;
			}
			else
			{
				PhantomBlowCollisionSpawnTime = 0.1f;
			}
		}
	}
}

void ACQ57::PhantomBlow(UCollision* _Left, UCollision* _Right)
{
	if (_Right->GetCollisionProfileName() == "PLAYER")
	{
		GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.07f);
		bIsPhantomBlowCollisionSpawn = false;
		GetCollision("PhantomBlow")->SetActive(false);
	}
}