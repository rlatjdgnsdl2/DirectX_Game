#include "PreCompile.h"
#include "Jurai.h"

#include "Sniping.h"
#include "DownChain.h"

AJurai::AJurai()
{

	SpriteRenderer->CreateAnimation("Spawn", "Elite_Spawn", 0, 7, 1.0f / 8, false);
	SpriteRenderer->CreateAnimation("Sniping", "Jurai_Sniping", 0, 22, 1.0f / 12, false);
	SpriteRenderer->CreateAnimation("Chain", "Jurai_Chain", 0, 15, 0.1f, false);
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
	FSM.CreateState(1, std::bind(&AJurai::UpdateSniping, this, std::placeholders::_1), std::bind(&AJurai::StartSniping, this));
	FSM.CreateState(2, std::bind(&AJurai::UpdateChain, this, std::placeholders::_1), std::bind(&AJurai::StartChain, this));

}

AJurai::~AJurai()
{
}

void AJurai::BeginPlay()
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

	Pattern = Random.RandomInt(1, 2);
	if (Pattern == 1)
	{
		SetActorLocation(FVector(700.0f * Dir, 0.0f));
	}
	else
	{
		SetActorLocation(FVector(PlayerPos.X + 200.0f * Dir, PlayerPos.Y));
	}
}

void AJurai::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AJurai::StartSniping()
{
	SpriteRenderer->ChangeAnimation("Sniping", true);
	SpriteRenderer->SetRelativeLocation(FVector(-40.0f, 50.0f, UContentsConst::MONSTER_ZPOS));
}

void AJurai::UpdateSniping(float _DeltaTime)
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
		case 15:
			ASniping* Sniping = GetWorld()->SpawnActor<ASniping>().get();
			Sniping->SetDir(Dir);
			Sniping->SetActorLocation(FVector(GetActorLocation().X + 100.0f * -Dir, 0.0f));
		}
		PrevIndex = CurIndex;
	}
}

void AJurai::StartChain()
{
	SpriteRenderer->ChangeAnimation("Chain", true);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 230.0f, UContentsConst::MONSTER_ZPOS));
}

void AJurai::UpdateChain(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		GetWorld()->SpawnActor<ADownChain>();
		Destroy();
		return;
	}
}

