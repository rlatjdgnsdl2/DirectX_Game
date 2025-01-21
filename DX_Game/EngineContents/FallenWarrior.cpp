#include "PreCompile.h"
#include "FallenWarrior.h"



AFallenWarrior::AFallenWarrior()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);

	SpriteRenderer->CreateAnimation("Spawn", "FallenWarrior_Spawn", 0, 13, 0.1f, false);
	SpriteRenderer->CreateAnimation("Stand", "FallenWarrior_Stand", 0, 7);
	SpriteRenderer->CreateAnimation("Move", "FallenWarrior_Move", 0, 7);
	SpriteRenderer->CreateAnimation("Attack", "FallenWarrior_Attack", 0, 11,0.1f,false);
	SpriteRenderer->CreateAnimation("Die", "FallenWarrior_Die", 0, 13,0.1f,false);
	SpriteRenderer->CreateAnimation("Hit", "FallenWarrior_Hit", 0, 0, 0.1f, false);

	Collision = CreateDefaultSubObject<UCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetRelativeScale3D(FVector(50.0f, 90.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(10.0f, 45.0f));

	AttackCollision = CreateDefaultSubObject<UCollision>().get();
	AttackCollision->SetupAttachment(RootComponent);
	AttackCollision->SetCollisionProfileName("MonsterAttack");
	AttackCollision->SetRelativeScale3D(FVector(120.0f, 90.0f, 1.0f));
	AttackCollision->SetRelativeLocation(FVector(-50.0f, 45.0f));


	AnimaionFSM.CreateState(Monster_State::Spawn, std::bind(&AFallenWarrior::UpdateSpawn,this,std::placeholders::_1), std::bind(&AFallenWarrior::StartSpawn, this));
	AnimaionFSM.CreateState(Monster_State::Stand, std::bind(&AFallenWarrior::UpdateStand, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartStand, this));
	AnimaionFSM.CreateState(Monster_State::Move, std::bind(&AFallenWarrior::UpdateMove, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartMove, this));
	AnimaionFSM.CreateState(Monster_State::Attack, std::bind(&AFallenWarrior::UpdateAttack, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartAttack, this));
	AnimaionFSM.CreateState(Monster_State::Die, std::bind(&AFallenWarrior::UpdateDie, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartDie, this));
	AnimaionFSM.CreateState(Monster_State::Hit, std::bind(&AFallenWarrior::UpdateHit, this, std::placeholders::_1), std::bind(&AFallenWarrior::StartHit, this));

}

AFallenWarrior::~AFallenWarrior()
{

}

void AFallenWarrior::BeginPlay()
{
	AMonster::BeginPlay();
	AnimaionFSM.ChangeState(Monster_State::Spawn);
	
}

void AFallenWarrior::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	AnimaionFSM.Update(_DeltaTime);

	if (UEngineInput::IsDown('1')) {
		AnimaionFSM.ChangeState(Monster_State::Die);
	}
	if (UEngineInput::IsDown('2')) {
		AnimaionFSM.ChangeState(Monster_State::Spawn);
	}
	if (UEngineInput::IsDown('3')) {
		AnimaionFSM.ChangeState(Monster_State::Stand);
	}
	if (UEngineInput::IsDown('4')) {
		AnimaionFSM.ChangeState(Monster_State::Attack);
	}
	if (UEngineInput::IsDown('5')) {
		AnimaionFSM.ChangeState(Monster_State::Move);
	}
	if (UEngineInput::IsDown('6')) {
		AnimaionFSM.ChangeState(Monster_State::Hit);
	}
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
		//AnimaionFSM.ChangeState(Monster_State::Stand);
		AnimaionFSM.ChangeState(Monster_State::Move);
	}
}

void AFallenWarrior::StartStand()
{
	SpriteRenderer->ChangeAnimation("Stand");
	SpriteRenderer->SetRelativeLocation(FVector(-15.0f, 65.0f, static_cast<float>(Z_ORDER::Monster)));
}

void AFallenWarrior::UpdateStand(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(Monster_State::Move);
	}
}

void AFallenWarrior::StartMove()
{
	SpriteRenderer->ChangeAnimation("Move");
	SpriteRenderer->SetRelativeLocation(FVector(-15.0f, 60.0f, static_cast<float>(Z_ORDER::Monster)));
}

void AFallenWarrior::UpdateMove(float _DeltaTime)
{
	
}

void AFallenWarrior::StartAttack()
{
	SpriteRenderer->ChangeAnimation("Attack",true);
	SpriteRenderer->SetRelativeLocation(FVector(-45.0f,50.0f, static_cast<float>(Z_ORDER::Monster)));
}

void AFallenWarrior::UpdateAttack(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(Monster_State::Stand);
	}
}

void AFallenWarrior::StartDie()
{
	SpriteRenderer->ChangeAnimation("Die", true);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f, 120.0f, static_cast<float>(Z_ORDER::Monster)));
}

void AFallenWarrior::UpdateDie(float _DeltaTime)
{
}

void AFallenWarrior::StartHit()
{
	SpriteRenderer->ChangeAnimation("Hit", true);
	SpriteRenderer->SetRelativeLocation(FVector(15.0f, 65.0f, static_cast<float>(Z_ORDER::Monster)));
}

void AFallenWarrior::UpdateHit(float _DeltaTime)
{
}
