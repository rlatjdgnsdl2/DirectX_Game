#include "PreCompile.h"
#include "FallenWarrior.h"

#include "Player.h"
#include "MyCollision.h"
#include "MyGameInstance.h"



AFallenWarrior::AFallenWarrior()
{
	SpriteRenderer->CreateAnimation("Spawn", "FallenWarrior_Spawn", 0, 13, 0.1f, false);
	SpriteRenderer->CreateAnimation("Stand", "FallenWarrior_Stand", 0, 7, 0.1f);
	SpriteRenderer->CreateAnimation("Move", "FallenWarrior_Move", 0, 7, 0.1f);
	SpriteRenderer->CreateAnimation("Attack", "FallenWarrior_Attack", 0, 11, 0.1f, false);
	SpriteRenderer->CreateAnimation("Die", "FallenWarrior_Die", 0, 13, 0.1f, false);
	SpriteRenderer->CreateAnimation("SelfDestroy", "FallenWarrior_SelfDestroy", 0, 22, 0.1f, false);

	BarriorRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	BarriorRenderer->SetupAttachment(RootComponent);
	BarriorRenderer->CreateAnimation("Barrior", "FallenWarrior_Barrior", 0, 7);
	BarriorRenderer->SetRelativeLocation(FVector(0.0f, 40.0f, UContentsConst::M_EFFECT_FRONT_ZPOS));

	{
		UMyCollision* Collision = GetCollision("Character");
		Collision->SetRelativeScale3D(FVector(50.0f, 90.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(10.0f, 45.0f));
		Collision->SetActive(false);
	}

	{
		UMyCollision* Collision = GetCollision("Attack");
		Collision->SetRelativeScale3D(FVector(100.0f, 90.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-50.0f, 45.0f));
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collision->SetCollisionStay(std::bind(&AFallenWarrior::Attack, this, std::placeholders::_1, std::placeholders::_1));

	}


	{
		UMyCollision* Collision = GetCollision("Scope");
		Collision->SetRelativeScale3D(FVector(150.0f, 200.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(-10.0f, 45.0f));
		Collision->SetColor(UContentsConst::SCOPE_COLOR);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				std::string ProfileName = _Right->GetCollisionProfileName();

				if (_Right->GetActor()->GetActorLocation().X <= GetActorLocation().X)
				{
					Dir = 1;
				}
				else
				{
					Dir = -1;
				}
				SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));
				GetCollision("Scope")->SetActive(false);
				FSM.ChangeState(Monster_State::Attack);

			});
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetRelativeScale3D(FVector(250.0f, 250.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(10.0f, 45.0f));
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetColor(UContentsConst::ATTACK_COLOR);
		Collision->SetCollisionStay(std::bind(&AFallenWarrior::SelfDestroy, this, std::placeholders::_1, std::placeholders::_1));
		Collision->SetActive(false);
		InsertCollision("SelfDestroy", Collision);
	}

	FSM.CreateState(Monster_State::Spawn, std::bind(&AFallenWarrior::UpdateSpawn, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartSpawn, this));
	FSM.CreateState(Monster_State::Stand, std::bind(&AFallenWarrior::UpdateStand, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartStand, this));
	FSM.CreateState(Monster_State::Move, std::bind(&AFallenWarrior::UpdateMove, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartMove, this));
	FSM.CreateState(Monster_State::Attack, std::bind(&AFallenWarrior::UpdateAttack, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartAttack, this));
	FSM.CreateState(Monster_State::Die, std::bind(&AFallenWarrior::UpdateDie, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartDie, this));
	FSM.CreateState(Monster_State::SelfDestroy, std::bind(&AFallenWarrior::UpdateSelfDestroy, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartSelfDestroy, this));


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
	Hp = UContentsConst::FALLEN_WARRIOR_HP;
	bIsDamagedable = false;
	FSM.ChangeState(Monster_State::Spawn);
	
}

void AFallenWarrior::Tick(float _DeltaTime)

{
	AMonster::Tick(_DeltaTime);
	SelfDestroyTime -= _DeltaTime;
	// 5초동안 무적
	if (!bIsDamagedable)
	{
		NoDamageTime -= _DeltaTime;
		if (NoDamageTime <= 0.0f)
		{
			bIsDamagedable = true;
			BarriorRenderer->SetActive(false);
		}
	}
	FSM.Update(_DeltaTime);
}

void AFallenWarrior::StartSpawn()
{
	SpriteRenderer->ChangeAnimation("Spawn", true);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 240.0f, UContentsConst::MONSTER_ZPOS));
}

void AFallenWarrior::UpdateSpawn(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		BarriorRenderer->ChangeAnimation("Barrior");
		FSM.ChangeState(Monster_State::Stand);
	}
}

void AFallenWarrior::StartStand()
{
	SpriteRenderer->ChangeAnimation("Stand");
	SpriteRenderer->SetRelativeLocation(FVector(-15.0f, 65.0f, UContentsConst::MONSTER_ZPOS));
	GetCollision("Character")->SetActive(true);
	GetCollision("Scope")->SetActive(true);
}

void AFallenWarrior::UpdateStand(float _DeltaTime)
{
	if (Hp <= 0.0f)
	{
		FSM.ChangeState(Monster_State::Die);
		return;
	}
	if (SelfDestroyTime <= 0.0f)
	{
		FSM.ChangeState(Monster_State::SelfDestroy);
		return;
	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(Monster_State::Move);
		return;
	}
}

void AFallenWarrior::StartMove()
{
	SpriteRenderer->ChangeAnimation("Move");
	SpriteRenderer->SetRelativeLocation(FVector(-15.0f, 60.0f, UContentsConst::MONSTER_ZPOS));
}

void AFallenWarrior::UpdateMove(float _DeltaTime)
{
	WalkTime += _DeltaTime;
	if (Hp <= 0.0f)
	{
		FSM.ChangeState(Monster_State::Die);
		return;
	}
	if (WalkTime >= 2.0f)
	{
		Dir = Random.RandomInt(-1, 1);
		if (Dir == 0)
		{
			FSM.ChangeState(Monster_State::Stand);
			return;
		}
		else
		{
			SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));
		}
		WalkTime = 0.0f;
	}
	AddActorLocation(FVector(-Dir * 20.0f * _DeltaTime, 0.0f, 0.0f));
}

void AFallenWarrior::StartAttack()
{
	SpriteRenderer->ChangeAnimation("Attack", true);
	SpriteRenderer->SetRelativeLocation(FVector(-45.0f, 50.0f, UContentsConst::MONSTER_ZPOS));
	GetCollision("Scope")->SetActive(false);
	AttackCollisionActiveTime = 0.0f;
}

void AFallenWarrior::UpdateAttack(float _DeltaTime)
{
	AttackCollisionActiveTime += _DeltaTime;
	if (Hp <= 0.0f)
	{
		FSM.ChangeState(Monster_State::Die);
		return;
	}
	if (!bIsAttackCollisionActive) {
		if (AttackCollisionActiveTime >= 0.6f)
		{
			GetCollision("Attack")->SetActive(true);
			bIsAttackCollisionActive = true;
		}
	}
	else
	{
		if (AttackCollisionActiveTime >= 0.8f)
		{
			GetCollision("Attack")->SetActive(false);
		}
	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		bIsAttackCollisionActive = false;
		AttackCollisionActiveTime = 0.0f;
		FSM.ChangeState(Monster_State::Stand);
		return;
	}
}

void AFallenWarrior::Attack(UCollision* _Left, UCollision* _Right)
{
	GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(AttackDamage);
	GetCollision("Attack")->SetActive(false);
}

void AFallenWarrior::StartDie()
{
	SpriteRenderer->ChangeAnimation("Die", true);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 120.0f, UContentsConst::MONSTER_ZPOS));
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

void AFallenWarrior::StartSelfDestroy()
{
	SpriteRenderer->ChangeAnimation("SelfDestroy", true);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 50.0f, UContentsConst::MONSTER_ZPOS));
	GetCollision("Scope")->SetActive(false);
	GetCollision("Attack")->SetActive(false);
}

void AFallenWarrior::UpdateSelfDestroy(float _DeltaTime)
{
	SelfDestroyCollisionActiveTime += _DeltaTime;
	if (!bIsSelfDestroyCollisionActive)
	{
		if (SelfDestroyCollisionActiveTime >= 1.2f)
		{
			GetCollision("SelfDestroy")->SetActive(true);
			bIsSelfDestroyCollisionActive = true;
		}
	}
	else
	{
		if (SelfDestroyCollisionActiveTime >= 1.6f)
		{
			GetCollision("SelfDestroy")->SetActive(false);
		}
	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
}

void AFallenWarrior::SelfDestroy(UCollision* _Left, UCollision* _Right)
{
	std::string ProfileName = _Right->GetCollisionProfileName();
	GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.1f);
	// 혼란상태이상추가
	GetCollision("SelfDestroy")->SetActive(false);
}


