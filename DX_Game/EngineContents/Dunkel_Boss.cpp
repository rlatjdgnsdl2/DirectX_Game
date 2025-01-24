#include "PreCompile.h"
#include "Dunkel_Boss.h"
#include "Player.h"

#include "MyCollision.h"
#include "MyGameInstance.h"
#include "Dunkel_SwordPower.h"


ADunkel_Boss::ADunkel_Boss()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);

	SpriteRenderer->CreateAnimation("Spawn", "Dunkel_Spawn", 0, 31, 3.0f / 32, false);
	SpriteRenderer->CreateAnimation("Stand", "Dunkel_Stand", 0, 12, 1.5f / 13);
	SpriteRenderer->CreateAnimation("Die", "Dunkel_Die", 0, 27, 3.0f / 28, false);

	SpriteRenderer->CreateAnimation("Up", "Dunkel_Up", 0, 15, 2 / 16.0f, false);
	SpriteRenderer->CreateAnimation("Down", "Dunkel_Down", 0, 14, 0.1f, false);
	SpriteRenderer->CreateAnimation("Force", "Dunkel_Force", 0, 24, 0.1f, false);
	SpriteRenderer->CreateAnimation("Knockback", "Dunkel_Knockback", 0, 29, 0.1f, false);
	SpriteRenderer->CreateAnimation("Meteo", "Dunkel_Meteo", 0, 23, 0.1f, false);
	SpriteRenderer->CreateAnimation("Slash_Start", "Dunkel_Slash_Start", 0, 10, 0.1f, false);
	SpriteRenderer->CreateAnimation("Slash_End", "Dunkel_Slash_End", 0, 15, 0.1f, false);
	SpriteRenderer->CreateAnimation("Sword", "Dunkel_SwordPower", 0, 19, 3.0f/20, false);

	AnimaionFSM.CreateState(DunkelAnim_State::Die, std::bind(&ADunkel_Boss::UpdateDie, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartDie, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Down, std::bind(&ADunkel_Boss::UpdateDown, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartDown, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Force, std::bind(&ADunkel_Boss::UpdateForce, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartForce, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Knockback, std::bind(&ADunkel_Boss::UpdateKnockback, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartKnockback, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Meteo, std::bind(&ADunkel_Boss::UpdateMeteo, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartMeteo, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Slash_End, std::bind(&ADunkel_Boss::UpdateSlash_End, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartSlash_End, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Slash_Start, std::bind(&ADunkel_Boss::UpdateSlash_Start, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartSlash_Start, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Spawn, std::bind(&ADunkel_Boss::UpdateSpawn, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartSpawn, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Stand, std::bind(&ADunkel_Boss::UpdateStand, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartStand, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Sword, std::bind(&ADunkel_Boss::UpdateSword, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartSword, this));
	AnimaionFSM.CreateState(DunkelAnim_State::Up, std::bind(&ADunkel_Boss::UpdateUp, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartUp, this));

	//	보스 콜리전
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("Boss");
		Collision->SetRelativeScale3D(FVector(150.0f, 320.0f, 1.0f));
		Collision->SetActive(false);
		InsertCollision("Character", Collision);
	}
	// 보스공격 콜리젼
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("BossAttack");
		Collision->SetRelativeScale3D(FVector(400.0f, 300.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(-200.0f, 300.0f, 0.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				float Dir = GetActorTransform().Scale.X;
				FPlayerLogic& LogicValue = Player->GetPlayerLogic();
				LogicValue.SetVelocityX(-Dir * 1000.0f);
				LogicValue.SetVelocityY(1000.0f);
				LogicValue.SetGravityAccel(0.0f);
				LogicValue.bIsJumpable = false;
				LogicValue.SetDownableFloor(false);
			});

		InsertCollision("Knockback", Collision);
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("BossAttack");
		Collision->SetRelativeScale3D(FVector(700.0f, 300.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(250.0f, 330.0f, 0.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.9f);
			});
		InsertCollision("Slash", Collision);

	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("BossAttack");
		Collision->SetRelativeScale3D(FVector(300.0f, 50.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(0.0f, 25.0f, 0.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.SetHpPercentDamage(0.6f);
				//스턴
				GetCollision("Down")->SetActive(false);
			});
		InsertCollision("Down", Collision);
	}
	GetWorld()->LinkCollisionProfile("BossAttack", "Player");
}

ADunkel_Boss::~ADunkel_Boss()
{

}

void ADunkel_Boss::BeginPlay()
{
	AMonster::BeginPlay();
	HP = 157500000000000.0f;
	AnimaionFSM.ChangeState(DunkelAnim_State::Spawn);
}

void ADunkel_Boss::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	AnimaionFSM.Update(_DeltaTime);

	if (UEngineInput::IsDown('1')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Die);
	}
	if (UEngineInput::IsDown('2')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Force);
	}
	if (UEngineInput::IsDown('3')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Knockback);
	}
	if (UEngineInput::IsDown('4')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Meteo);
	}
	if (UEngineInput::IsDown('5')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Slash_Start);
	}
	if (UEngineInput::IsDown('6')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Spawn);
	}
	if (UEngineInput::IsDown('7')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
	}

	if (UEngineInput::IsDown('8')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Sword);
	}
	if (UEngineInput::IsDown('9')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Up);
	}

	if (UEngineInput::IsDown('0')) {

	}



}

void ADunkel_Boss::StartSpawn()
{
	SpriteRenderer->ChangeAnimation("Spawn", true);
	SpriteRenderer->SetRelativeLocation(FVector(-20.0f, 200.0f, static_cast<float>(Z_ORDER::Boss)));
}

void ADunkel_Boss::UpdateSpawn(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}

void ADunkel_Boss::StartStand()
{
	SpriteRenderer->ChangeAnimation("Stand");
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 180.0f, static_cast<float>(Z_ORDER::Boss)));
	GetCollision("Character")->SetActive(true);
	GetCollision("Character")->SetRelativeLocation(FVector(10.0f, 170.0f));
}

void ADunkel_Boss::UpdateStand(float _DeltaTime)
{

}


void ADunkel_Boss::StartDie()
{
	SpriteRenderer->ChangeAnimation("Die", true);
	SpriteRenderer->SetRelativeLocation(FVector(-60.0f, 180.0f, static_cast<float>(Z_ORDER::Boss)));
	GetCollision("Character")->SetActive(false);
}

void ADunkel_Boss::UpdateDie(float _DeltaTime)
{

}



void ADunkel_Boss::StartKnockback()
{
	SpriteRenderer->ChangeAnimation("Knockback", true);
	SpriteRenderer->SetRelativeLocation(FVector(-210.0f, 200.0f, static_cast<float>(Z_ORDER::Boss)));
}

void ADunkel_Boss::UpdateKnockback(float _DeltaTime)
{
	CollisonSpawnTime += _DeltaTime;
	if (bIsAttack)
	{
		if (CollisonSpawnTime > 2.1f) {
			GetCollision("Knockback")->SetActive(false);
		}
		if (CollisonSpawnTime > 2.0f) {
			GetCollision("Knockback")->SetActive(true);
		}
		if (SpriteRenderer->IsCurAnimationEnd())
		{
			CollisonSpawnTime = 0.0f;
			AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
			return;
		}
	}
}
void ADunkel_Boss::StartForce()
{
	SpriteRenderer->ChangeAnimation("Force", true);
	SpriteRenderer->SetRelativeLocation(FVector(-120.0f, 360.0f, static_cast<float>(Z_ORDER::Boss)));
}

void ADunkel_Boss::UpdateForce(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}


void ADunkel_Boss::StartMeteo()
{
	SpriteRenderer->ChangeAnimation("Meteo", true);
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 320.0f, static_cast<float>(Z_ORDER::Boss)));
}

void ADunkel_Boss::UpdateMeteo(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}

void ADunkel_Boss::StartSlash_Start()
{
	SpriteRenderer->ChangeAnimation("Slash_Start", true);
	SpriteRenderer->SetRelativeLocation(FVector(-60.0f, 170.0f, static_cast<float>(Z_ORDER::Boss)));
}

void ADunkel_Boss::UpdateSlash_Start(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(DunkelAnim_State::Slash_End);
		return;
	}
}

void ADunkel_Boss::StartSlash_End()
{
	SpriteRenderer->ChangeAnimation("Slash_End", true);
	SpriteRenderer->SetRelativeLocation(FVector(200.0f, 240.0f, static_cast<float>(Z_ORDER::Boss)));
	GetCollision("Slash")->SetActive(true);

}

void ADunkel_Boss::UpdateSlash_End(float _DeltaTime)
{
	CollisonSpawnTime += _DeltaTime;
	if (CollisonSpawnTime > 0.3f) {
		GetCollision("Slash")->SetActive(false);
	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		CollisonSpawnTime = 0.0f;
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}




void ADunkel_Boss::StartSword()
{
	SpriteRenderer->ChangeAnimation("Sword", true);
	SpriteRenderer->SetRelativeLocation(FVector(60.0f, 200.0f, static_cast<float>(Z_ORDER::Boss)));
	GetWorld()->SpawnActor<ADunkel_SwordPower>().get();
}

void ADunkel_Boss::UpdateSword(float _DeltaTime)
{

	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}

void ADunkel_Boss::StartUp()
{
	SpriteRenderer->ChangeAnimation("Up", true);
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 180.0f, static_cast<float>(Z_ORDER::Boss)));
	GetCollision("Character")->SetActive(false);
}

void ADunkel_Boss::UpdateUp(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(DunkelAnim_State::Down);
		return;
	}
}

void ADunkel_Boss::StartDown()
{
	SpriteRenderer->ChangeAnimation("Down", true);
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 400.0f, static_cast<float>(Z_ORDER::Boss)));
	GetCollision("Character")->SetActive(true);
	GetCollision("Down")->SetActive(true);
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
	if (PlayerPos.X < GetActorLocation().X)
	{
		Dir = 1;
	}
	else
	{
		Dir = -1;
	}
	SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));
	SetActorLocation(FVector(PlayerPos.X, 0.0f));
}

void ADunkel_Boss::UpdateDown(float _DeltaTime)
{
	CollisonSpawnTime += _DeltaTime;
	if (CollisonSpawnTime > 0.3f)
	{
		GetCollision("Down")->SetActive(false);
	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		CollisonSpawnTime = 0.0f;
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}
