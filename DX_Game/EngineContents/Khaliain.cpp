#include "PreCompile.h"
#include "Khaliain.h"

#include "UpChain.h"
#include "MagicSphere.h"

AKhaliain::AKhaliain()
{
	SpriteRenderer->CreateAnimation("Spawn", "Elite_Spawn", 0, 7, 1.0f / 8, false);
	SpriteRenderer->CreateAnimation("Magic", "Khaliain_MagicSphere", 0, 19, 1.0f / 12, false);
	SpriteRenderer->CreateAnimation("Chain", "Khaliain_Chain", 0, 19, 0.1f, false);

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
				Pattern = Random.RandomInt(1, 2);
				FSM.ChangeState(Pattern);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Spawn", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 110.0f, UContentsConst::MONSTER_ZPOS));
		});
	FSM.CreateState(1, std::bind(&AKhaliain::UpdateMagic, this, std::placeholders::_1), std::bind(&AKhaliain::StartMagic, this));
	FSM.CreateState(2, std::bind(&AKhaliain::UpdateChain, this, std::placeholders::_1), std::bind(&AKhaliain::StartChain, this));

}

AKhaliain::~AKhaliain()
{
}

void AKhaliain::BeginPlay()
{
	AMonster::BeginPlay();
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
	FSM.ChangeState(0);
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
	SetActorLocation(FVector(PlayerPos.X + 200.0f * Dir, PlayerPos.Y));
}

void AKhaliain::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AKhaliain::StartMagic()
{
	SpriteRenderer->ChangeAnimation("Magic", true);
	SpriteRenderer->SetRelativeLocation(FVector(-40.0f, 150.0f, UContentsConst::MONSTER_ZPOS));
}

void AKhaliain::UpdateMagic(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AMagicSphere* Magic = GetWorld()->SpawnActor<AMagicSphere>().get();
		Magic->SetDir(Dir);
		Destroy();
		return;
	}
}

void AKhaliain::StartChain()
{
	SpriteRenderer->ChangeAnimation("Chain", true);
	SpriteRenderer->SetRelativeLocation(FVector(-40.0f, 150.0f, UContentsConst::MONSTER_ZPOS));
}

void AKhaliain::UpdateChain(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		std::shuffle(ChainPosX.begin(), ChainPosX.end(), Random.GetMtGen());
		for (int i = 0; i < 7; i++)
		{
			AUpChain* Chain = GetWorld()->SpawnActor<AUpChain>().get();
			Chain->SetActorLocation(FVector(ChainPosX[i], 0.0f));
		}
		Destroy();
		return;
	}
}
