#include "PreCompile.h"
#include "Freyd.h"
#include "Shot.h"

AFreyd::AFreyd()
{
	SpriteRenderer->CreateAnimation("Spawn", "Elite_Spawn", 0, 7, 0.1f, false);
	SpriteRenderer->CreateAnimation("Fist", "Freyd_Inlage", 0, 14, 0.1f, false);
	SpriteRenderer->CreateAnimation("Shot", "Freyd_HeadShoot", 0, 18, 0.1f, false);


	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(300.0f, 200.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-130.0f, 80.0f, 0.0f));
		Collision->SetCollisionStay(std::bind(&AFreyd::Fist, this, std::placeholders::_1, std::placeholders::_1));
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collision->SetActive(false);
		InsertCollision("Fist", Collision);
	}

	{
		UMyCollision* Collision = GetCollision("Character");
		Collision->SetCollisionProfileName("EliteMonster");
		Collision->SetRelativeScale3D(FVector(200.0f, 200.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
	}

	FSM.CreateState(0,
		[this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				
				FSM.ChangeState(Pattern);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Spawn", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 110.0f, UContentsConst::MONSTER_ZPOS));
		});
	FSM.CreateState(1, std::bind(&AFreyd::UpdateShot, this, std::placeholders::_1), std::bind(&AFreyd::StartShot, this));
	FSM.CreateState(2, std::bind(&AFreyd::UpdateFist, this, std::placeholders::_1), std::bind(&AFreyd::StartFist, this));
}

AFreyd::~AFreyd()
{


}

void AFreyd::BeginPlay()
{
	AMonster::BeginPlay();
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
	FSM.ChangeState(0);
	Pattern = Random.RandomInt(1, 2);
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
	if (Pattern == 1)
	{
		SetActorLocation(FVector(PlayerPos.X, 0.0f));
	}
	else
	{
		SetActorLocation(FVector(PlayerPos.X + 200.0f * Dir, 0.0f));
	}

}

void AFreyd::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AFreyd::StartShot()
{
	SpriteRenderer->ChangeAnimation("Shot", true);
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 150.0f, UContentsConst::MONSTER_ZPOS));

}

void AFreyd::UpdateShot(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		std::shuffle(ShotPosX.begin(), ShotPosX.end(), Random.GetMtGen());
		for (int i = 0; i < 7; i++)
		{
			AShot* Shot = GetWorld()->SpawnActor<AShot>().get();
			Shot->SetActorLocation(FVector(ShotPosX[i], 0.0f));
		}
		Destroy();
		return;
	}
}

void AFreyd::StartFist()
{
	SpriteRenderer->ChangeAnimation("Fist", true);
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 130.0f, UContentsConst::MONSTER_ZPOS));
}

void AFreyd::UpdateFist(float _DeltaTime)
{
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
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			GetCollision("Fist")->SetActive(true);
			break;
		case 10:
			GetCollision("Fist")->SetActive(false);
			break;
		}
		PrevIndex = CurIndex;
	}
}

void AFreyd::Fist(UCollision* _Left, UCollision* _Right)
{
	GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.05f);
	GetCollision("Fist")->SetActive(false);
}


