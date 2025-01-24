#include "PreCompile.h"
#include "FallenWarrior.h"

#include "Player.h"
#include "MyCollision.h"
#include "MyGameInstance.h"



AFallenWarrior::AFallenWarrior()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);

	SpriteRenderer->CreateAnimation("Spawn", "FallenWarrior_Spawn", 0, 13, 1.5f / 14, false);
	SpriteRenderer->CreateAnimation("Stand", "FallenWarrior_Stand", 0, 7, 1.5f / 8);
	SpriteRenderer->CreateAnimation("Move", "FallenWarrior_Move", 0, 7, 1.5f / 8);
	SpriteRenderer->CreateAnimation("Attack", "FallenWarrior_Attack", 0, 11, 1.5f / 12, false);
	SpriteRenderer->CreateAnimation("Die", "FallenWarrior_Die", 0, 13, 1.5f / 14, false);

	Barrior = CreateDefaultSubObject<USpriteRenderer>().get();
	Barrior->SetupAttachment(RootComponent);
	Barrior->CreateAnimation("Barrior", "FallenWarrior_Barrior", 0, 7);
	Barrior->SetRelativeLocation(FVector(0.0f, 40.0f, static_cast<float>(Z_ORDER::Skill_Back)));
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("Monster");
		Collision->SetRelativeScale3D(FVector(50.0f, 90.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(10.0f, 45.0f));
		InsertCollision("Character", Collision);
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetRelativeScale3D(FVector(100.0f, 90.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-50.0f, 45.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				if (_Right->GetCollisionProfileName() == "PLAYER")
				{
					GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.1f);
					if (GetCollision("Attack") == nullptr)
					{
						return;
					}
					GetCollision("Attack")->SetActive(false);
				}
			});
		InsertCollision("Attack", Collision);
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("Scope");
		Collision->SetRelativeScale3D(FVector(200.0f, 200.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-10.0f, 45.0f));
		Collision->SetColor(UContentsConst::SCOPE_COLOR);

		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				if (_Right->GetActor()->GetActorLocation().X <= GetActorLocation().X)
				{
					SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
				}
				else
				{
					SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
				}
				AnimaionFSM.ChangeState(Monster_State::Attack);
			});
		InsertCollision("Scope", Collision);
	}

	AnimaionFSM.CreateState(Monster_State::Spawn, std::bind(&AFallenWarrior::UpdateSpawn, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartSpawn, this));
	AnimaionFSM.CreateState(Monster_State::Stand, std::bind(&AFallenWarrior::UpdateStand, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartStand, this));
	AnimaionFSM.CreateState(Monster_State::Move, std::bind(&AFallenWarrior::UpdateMove, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartMove, this));
	AnimaionFSM.CreateState(Monster_State::Attack, std::bind(&AFallenWarrior::UpdateAttack, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartAttack, this));
	AnimaionFSM.CreateState(Monster_State::Die, std::bind(&AFallenWarrior::UpdateDie, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartDie, this));


	// Monster, MonsterAttack, Scope
	GetWorld()->LinkCollisionProfile("Scope", "Player");
	GetWorld()->LinkCollisionProfile("MonsterAttack", "Player");
}

AFallenWarrior::~AFallenWarrior()
{

}

void AFallenWarrior::BeginPlay()
{
	AMonster::BeginPlay();
	HP = 300'0000'0000.0f;
	bIsDamagedable = false;
	AnimaionFSM.ChangeState(Monster_State::Spawn);
	Barrior->ChangeAnimation("Barrior");
}

void AFallenWarrior::Tick(float _DeltaTime)

{
	AMonster::Tick(_DeltaTime);
	if (bIsDamagedable == false)
	{
		NoDamageTime -= _DeltaTime;
		if (NoDamageTime <= 0.0f)
		{
			bIsDamagedable = true;
			Barrior->SetActive(false);
		}
	}
	AnimaionFSM.Update(_DeltaTime);
}

void AFallenWarrior::StartSpawn()
{
	SpriteRenderer->ChangeAnimation("Spawn", true);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 240.0f, static_cast<float>(Z_ORDER::Monster)));
}

void AFallenWarrior::UpdateSpawn(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(Monster_State::Stand);
	}
}

void AFallenWarrior::StartStand()
{
	SpriteRenderer->ChangeAnimation("Stand");
	SpriteRenderer->SetRelativeLocation(FVector(-15.0f, 65.0f, static_cast<float>(Z_ORDER::Monster)));
	GetCollision("Attack")->SetActive(false);
	GetCollision("Scope")->SetActive(true);
}

void AFallenWarrior::UpdateStand(float _DeltaTime)
{
	if (HP <= 0.0f)
	{
		AnimaionFSM.ChangeState(Monster_State::Die);
		return;
	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(Monster_State::Move);
		return;
	}
}

void AFallenWarrior::StartMove()
{
	SpriteRenderer->ChangeAnimation("Move");
	SpriteRenderer->SetRelativeLocation(FVector(-15.0f, 60.0f, static_cast<float>(Z_ORDER::Monster)));
}

void AFallenWarrior::UpdateMove(float _DeltaTime)
{
	WalkTime -= _DeltaTime;
	if (HP <= 0.0f)
	{
		AnimaionFSM.ChangeState(Monster_State::Die);
		return;
	}
	if (WalkTime <= 0.0f)
	{
		Dir = Random.RandomInt(-1, 1);
		if (Dir == 1) {
			SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
		}
		else if (Dir == -1) {
			SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
		}
		else if (Dir == 0) {
			AnimaionFSM.ChangeState(Monster_State::Stand);
			return;
		}
		WalkTime = 1.5f;
	}
	AddActorLocation(FVector(Dir * 20.0f * _DeltaTime, 0.0f, 0.0f));
}

void AFallenWarrior::StartAttack()
{
	SpriteRenderer->ChangeAnimation("Attack", true);
	SpriteRenderer->SetRelativeLocation(FVector(-45.0f, 50.0f, static_cast<float>(Z_ORDER::Monster)));
	GetCollision("Scope")->SetActive(false);
}

void AFallenWarrior::UpdateAttack(float _DeltaTime)
{
	AttackDelay -= _DeltaTime;
	if (HP <= 0.0f)
	{
		AnimaionFSM.ChangeState(Monster_State::Die);
		return;
	}
	if (!bIsAttack) {
		if (AttackDelay <= 0.0f)
		{
			GetCollision("Attack")->SetActive(true);
			bIsAttack = true;
		}
	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AttackDelay = 0.5f;
		bIsAttack = false;
		AnimaionFSM.ChangeState(Monster_State::Stand);
		return;
	}
}

void AFallenWarrior::StartDie()
{
	SpriteRenderer->ChangeAnimation("Die", true);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 120.0f, static_cast<float>(Z_ORDER::Monster)));
	GetCollision("Scope")->SetActive(false);
	GetCollision("Attack")->SetActive(false);
}

void AFallenWarrior::UpdateDie(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}


