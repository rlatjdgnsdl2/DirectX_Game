#include "PreCompile.h"
#include "Dunkel_Boss.h"
#include "Player.h"
#include "FallenWarrior.h"

#include "MyCollision.h"


ADunkel_Boss::ADunkel_Boss()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);

	SpriteRenderer->CreateAnimation("Die", "Dunkel_Die", 0, 27, 0.1f, false);
	SpriteRenderer->CreateAnimation("Down", "Dunkel_Down", 0, 14, 0.1f, false);
	SpriteRenderer->CreateAnimation("Force", "Dunkel_Force", 0, 24, 0.1f, false);
	SpriteRenderer->CreateAnimation("Knockback", "Dunkel_Knockback", 0, 29, 0.1f, false);
	SpriteRenderer->CreateAnimation("Meteo", "Dunkel_Meteo", 0, 23, 0.1f, false);
	SpriteRenderer->CreateAnimation("Slash_End", "Dunkel_Slash_End", 0, 15, 0.1f, false);
	SpriteRenderer->CreateAnimation("Slash_Start", "Dunkel_Slash_Start", 0, 10, 0.1f, false);
	SpriteRenderer->CreateAnimation("Spawn", "Dunkel_Spawn", 0, 31, 0.1f, false);
	SpriteRenderer->CreateAnimation("Stand", "Dunkel_Stand", 0, 12);
	SpriteRenderer->CreateAnimation("Sword", "Dunkel_SwordPower", 0, 19, 0.1f, false);
	SpriteRenderer->CreateAnimation("Up", "Dunkel_Up", 0, 15, 0.1f, false);

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
	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Boss");
	Collision->GetRenderUnit().SetTexture("ImageTexture", "DebugCollisionBase.png");
	Collision->SetRelativeScale3D(FVector(150.0f, 320.0f, 1.0f));
	// 보스공격 콜리젼
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetActive(false);
		Collision->SetRelativeScale3D(FVector(400.0f, 300.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(-200.0f, 300.0f, 0.0f));
		Collision->SetCollisionProfileName("BossAttack");
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
		AttackCollisionMap.insert(std::make_pair("Knockback", Collision));
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetActive(false);
		Collision->SetRelativeScale3D(FVector(700.0f, 300.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(250.0f, 330.0f, 0.0f));
		Collision->SetCollisionProfileName("BossAttack");
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{

			});
		AttackCollisionMap.insert(std::make_pair("Slash", Collision));
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetActive(false);
		Collision->SetRelativeScale3D(FVector(300.0f, 50.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(50.0f, 150.0f, 0.0f));
		Collision->SetCollisionProfileName("BossAttack");
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{

			});
		AttackCollisionMap.insert(std::make_pair("Down", Collision));
	}


	GetWorld()->LinkCollisionProfile("BossAttack", "Player");


}

ADunkel_Boss::~ADunkel_Boss()
{

}

void ADunkel_Boss::BeginPlay()
{
	AMonster::BeginPlay();
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



}

void ADunkel_Boss::StartDie()
{
	SpriteRenderer->ChangeAnimation("Die", true);
	SpriteRenderer->SetRelativeLocation(FVector(-60.0f, 180.0f, static_cast<float>(Z_ORDER::Boss)));
	Collision->SetActive(false);
}

void ADunkel_Boss::UpdateDie(float _DeltaTime)
{
}

void ADunkel_Boss::StartForce()
{
	SpriteRenderer->ChangeAnimation("Force", true);
	SpriteRenderer->SetRelativeLocation(FVector(-120.0f, 360.0f, static_cast<float>(Z_ORDER::Boss)));
	Collision->SetActive(true);
}

void ADunkel_Boss::UpdateForce(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}

void ADunkel_Boss::StartKnockback()
{

	SpriteRenderer->ChangeAnimation("Knockback");
	SpriteRenderer->SetRelativeLocation(FVector(-210.0f, 200.0f, static_cast<float>(Z_ORDER::Boss)));
	Collision->SetActive(true);

}

void ADunkel_Boss::UpdateKnockback(float _DeltaTime)
{
	CurTime += _DeltaTime;
	if (CurTime > 1.7f) {
		AttackCollisionMap["Knockback"]->SetActive(true);

	}
	if (CurTime > 1.8f) {
		AttackCollisionMap["Knockback"]->SetActive(false);

	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		CurTime = 0.0f;
		AttackCollisionMap["Knockback"]->SetActive(false);
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
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
	AttackCollisionMap["Slash"]->SetActive(true);

	SpriteRenderer->ChangeAnimation("Slash_End", true);
	SpriteRenderer->SetRelativeLocation(FVector(200.0f, 240.0f, static_cast<float>(Z_ORDER::Boss)));

}

void ADunkel_Boss::UpdateSlash_End(float _DeltaTime)
{
	CurTime += _DeltaTime;
	if (CurTime > 0.3f) {
		AttackCollisionMap["Slash"]->SetActive(false);

	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		CurTime = 0.0f;
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}

void ADunkel_Boss::StartSpawn()
{
	SpriteRenderer->ChangeAnimation("Spawn", true);
	SpriteRenderer->SetRelativeLocation(FVector(-20.0f, 200.0f, static_cast<float>(Z_ORDER::Boss)));
	Collision->SetActive(false);

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
	Collision->SetActive(true);
	Collision->SetRelativeLocation(FVector(10.0f, 170.0f));
}

void ADunkel_Boss::UpdateStand(float _DeltaTime)
{

}


void ADunkel_Boss::StartSword()
{
	SpriteRenderer->ChangeAnimation("Sword", true);
	SpriteRenderer->SetRelativeLocation(FVector(60.0f, 200.0f, static_cast<float>(Z_ORDER::Boss)));
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
	Collision->SetActive(false);
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
	AttackCollisionMap["Down"]->SetActive(true);
}

void ADunkel_Boss::UpdateDown(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
		return;
	}
}
