#include "PreCompile.h"
#include "CQ57.h"
#include "MyGameInstance.h"
#include "Player.h"
#include "PhysicsComponent.h"


ACQ57::ACQ57()
{

	SpriteRenderer->CreateAnimation("Spawn", "Elite_Spawn", 0, 7, 1.0f / 8, false);
	SpriteRenderer->CreateAnimation("KnockBack", "CQ57_KnockBack", 0, 26, 1.0f / 12, false);
	SpriteRenderer->CreateAnimation("PhantomBlow", "CQ57_PhantomBlow", 0, 13, 0.1f, false);

	{
		UMyCollision* Collision = GetCollision("Character");
		Collision->SetCollisionProfileName("EliteMonster");
		Collision->SetRelativeScale3D(FVector(200.0f, 200.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
	}



	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(250.0f, 150.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-130.0f, 60.0f, 0.0f));
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				if (Player == nullptr)
				{
					return;
				}
				Player->ChangeState(EPlayer_State::KnockBack);
				Player->GetPysicComponent()->SetVelocity(FVector(-Dir * 1000.0f, 1000.0f, 0.0f));
				GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.2f);
				GetCollision("Knockback")->SetActive(false);
			});
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
	SetActorLocation(FVector(PlayerPos.X + 100.0f * Dir, PlayerPos.Y));
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
	if (CurIndex >= 13)
	{
		CurTime += _DeltaTime;
		SetActorLocation(FVector(UEngineMath::Lerp(StartPosX, TargetPosX, UEngineMath::Clamp(CurTime / 0.1f, 0.0f, 1.0f)), 0.0f, 1.0f));
	}
	if (CurIndex != PrevIndex)
	{
		switch (CurIndex)
		{
		case 13:
			GetCollision("KnockBack")->SetActive(true);
			break;
		case 16:
			GetCollision("KnockBack")->SetActive(false);
			break;
		default:
			break;
		}
		PrevIndex = CurIndex;
	}

}

void ACQ57::KnockBack(UCollision* _Left, UCollision* _Right)
{
	

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

	if (CurIndex != PrevIndex)
	{
		switch (CurIndex)
		{
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
			GetCollision("PhantomBlow")->SetActive(true);
			break;
		case 10:
			GetCollision("PhantomBlow")->SetActive(false);
			break;
		default:
			break;
		}
		PrevIndex = CurIndex;
	}

}

void ACQ57::PhantomBlow(UCollision* _Left, UCollision* _Right)
{
	GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.07f);
	GetCollision("PhantomBlow")->SetActive(false);
}