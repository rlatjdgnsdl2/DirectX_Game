#include "PreCompile.h"
#include "Mogadin.h"

AMogadin::AMogadin()
{
	SpriteRenderer->CreateAnimation("Spawn", "Elite_Spawn", 0, 7, 1.0f / 8, false);
	SpriteRenderer->CreateAnimation("Slash", "Mogadin_Slash", 0, 17, 1.0f / 12, false);
	SpriteRenderer->CreateAnimation("Chain", "Mogadin_Chain", 0, 14, 0.1f, false);


	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(250.0f, 150.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-130.0f, 60.0f, 0.0f));
		Collision->SetCollisionStay(std::bind(&AMogadin::Slash, this, std::placeholders::_1, std::placeholders::_1));
		Collision->SetActive(false);
		InsertCollision("Slash", Collision);
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
	FSM.CreateState(1, std::bind(&AMogadin::UpdateSlash, this, std::placeholders::_1), std::bind(&AMogadin::StartSlash, this));
	FSM.CreateState(2, std::bind(&AMogadin::UpdateChain, this, std::placeholders::_1), std::bind(&AMogadin::StartChain, this));
}

AMogadin::~AMogadin()
{
}

void AMogadin::BeginPlay()
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

void AMogadin::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AMogadin::StartSlash()
{
	SpriteRenderer->ChangeAnimation("Slash", true);
	SpriteRenderer->SetRelativeLocation(FVector(60.0f, 110.0f, UContentsConst::MONSTER_ZPOS));
}

void AMogadin::UpdateSlash(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
	if (SlashCount < 0)
	{
		return;
	}

	SlashCollisionSpawnTime -= _DeltaTime;
	if (!bIsSlashCollisionSpawn)
	{
		if (SlashCollisionSpawnTime < 0.0f)
		{
			GetCollision("Slash")->SetActive(true);
			bIsSlashCollisionSpawn = true;
			SlashCount--;
			if (SlashCount == 3)
			{
				//PhantomBlowCollisionSpawnTime = 0.3f;
			}
			else
			{
				//PhantomBlowCollisionSpawnTime = 0.1f;
			}
		}
	}
}

void AMogadin::Slash(UCollision* _Left, UCollision* _Right)
{
	GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.09f);
	GetCollision("KnockBack")->SetActive(false);
}

void AMogadin::StartChain()
{
	SpriteRenderer->ChangeAnimation("Chain", true);
	SpriteRenderer->SetRelativeLocation(FVector(60.0f, 110.0f, UContentsConst::MONSTER_ZPOS));
}

void AMogadin::UpdateChain(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
}

void AMogadin::Chain(UCollision* _Left, UCollision* _Right)
{
}
