#include "PreCompile.h"
#include "Dunkel_Boss.h"
#include "Player.h"

#include "MyCollision.h"
#include "MyGameInstance.h"
#include "Dunkel_SwordPower.h"
#include "Dunkel_Meteo.h"

#include "CQ57.h"
#include "Freyd.h"
#include "Jurai.h"
#include "Khaliain.h"
#include "Mogadin.h"

#include "FallenWarrior.h"
#include "PillarLight.h"

#include "DownChain.h"


ADunkel_Boss::ADunkel_Boss()
{
	SpriteRenderer->CreateAnimation("Spawn", "Dunkel_Spawn", 0, 31, 3.0f / 32, false);
	SpriteRenderer->CreateAnimation("Stand", "Dunkel_Stand", 0, 12, 1.5f / 13);
	SpriteRenderer->CreateAnimation("Die", "Dunkel_Die", 0, 27, 3.0f / 28, false);

	SpriteRenderer->CreateAnimation("Up", "Dunkel_Up", 0, 15, 2 / 16.0f, false);
	SpriteRenderer->CreateAnimation("Down", "Dunkel_Down", 0, 14, 0.1f, false);
	SpriteRenderer->CreateAnimation("Force", "Dunkel_Force", 0, 24, 0.1f, false);
	SpriteRenderer->CreateAnimation("Knockback", "Dunkel_Knockback", 0, 29, 2.0f / 16, false);
	SpriteRenderer->CreateAnimation("Meteo", "Dunkel_Meteo", 0, 23, 0.1f, false);
	SpriteRenderer->CreateAnimation("Slash_Start", "Dunkel_Slash_Start", 0, 10, 0.1f, false);
	SpriteRenderer->CreateAnimation("Slash_End", "Dunkel_Slash_End", 0, 15, 0.1f, false);
	SpriteRenderer->CreateAnimation("Sword", "Dunkel_SwordPower", 0, 19, 3.0f / 20, false);


	{
		UMyCollision* Collision = GetCollision("Character");
		Collision->SetRelativeScale3D(FVector(150.0f, 320.0f, 1.0f));
		Collision->SetActive(false);
	}
	{
		UMyCollision* Collision = GetCollision("Scope");
		Collision->SetRelativeScale3D(FVector(600.0f, 320.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(10.0f, 170.0f));
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				if (_Right->GetCollisionProfileName() == "PLAYER")
				{
					bIsScopePlayer = true;
				}
			});
		Collision->SetCollisionEnd([this](UCollision* _Left, UCollision* _Right)
			{
				if (_Right->GetCollisionProfileName() == "PLAYER")
				{
					bIsScopePlayer = false;
				}
			});
	}

	// 듄켈 패턴 콜리전
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("BossAttack");
		Collision->SetRelativeScale3D(FVector(400.0f, 300.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(-200.0f, 150.0f, 0.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				
			});
		InsertCollision("Knockback", Collision);
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("BossAttack");
		Collision->SetRelativeScale3D(FVector(700.0f, 300.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(250.0f, 200.0f, 0.0f));
		Collision->SetActive(false);
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.9f);
				GetCollision("Slash")->SetActive(false);
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
				GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.6f);
				//스턴 추가
				GetCollision("Down")->SetActive(false);
			});
		InsertCollision("Down", Collision);
	}

	FSM.CreateState(EDunkelAnim_State::Spawn, std::bind(&ADunkel_Boss::UpdateSpawn, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartSpawn, this));
	FSM.CreateState(EDunkelAnim_State::Stand, std::bind(&ADunkel_Boss::UpdateStand, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartStand, this));
	FSM.CreateState(EDunkelAnim_State::Die, std::bind(&ADunkel_Boss::UpdateDie, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartDie, this));

	FSM.CreateState(EDunkelAnim_State::Up, std::bind(&ADunkel_Boss::UpdateUp, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartUp, this));
	FSM.CreateState(EDunkelAnim_State::Down, std::bind(&ADunkel_Boss::UpdateDown, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartDown, this));
	FSM.CreateState(EDunkelAnim_State::Force, std::bind(&ADunkel_Boss::UpdateForce, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartForce, this));
	FSM.CreateState(EDunkelAnim_State::Knockback, std::bind(&ADunkel_Boss::UpdateKnockback, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartKnockback, this));
	FSM.CreateState(EDunkelAnim_State::Meteo, std::bind(&ADunkel_Boss::UpdateMeteo, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartMeteo, this));
	FSM.CreateState(EDunkelAnim_State::Slash_Start, std::bind(&ADunkel_Boss::UpdateSlash_Start, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartSlash_Start, this));
	FSM.CreateState(EDunkelAnim_State::Slash_End, std::bind(&ADunkel_Boss::UpdateSlash_End, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartSlash_End, this));
	FSM.CreateState(EDunkelAnim_State::Sword, std::bind(&ADunkel_Boss::UpdateSword, this, std::placeholders::_1), std::bind(&ADunkel_Boss::StartSword, this));

	GetWorld()->LinkCollisionProfile("BossAttack", "Player");

	FallenWarriorSpawnPosX = { -600.0f, -550.0f, -500.0f, -450.0f, -400.0f,
						   -350.0f, -300.0f, -250.0f, -200.0f, -150.0f,
						   -100.0f, -50.0f, 0.0f, 50.0f, 100.0f,
						   150.0f, 200.0f, 250.0f, 300.0f, 350.0f,
						   400.0f, 450.0f, 500.0f, 550.0f, 600.0f };
	PillarLightPosX = { -520.0f,-395.0f, -270.0f,-145.0f,-20.0f,105.0f, 230.0f,355.0f,480.0f };
}

ADunkel_Boss::~ADunkel_Boss()
{

}

void ADunkel_Boss::BeginPlay()
{
	AMonster::BeginPlay();
	MaxHp = UContentsConst::DUNKEL_HP;
	Hp = UContentsConst::DUNKEL_HP;
	FSM.ChangeState(EDunkelAnim_State::Spawn);
}

void ADunkel_Boss::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	HpPercent = static_cast<float>(Hp) / static_cast<float>(MaxHp);
	SlashCoolTime -= _DeltaTime;
	SwordCoolTime -= _DeltaTime;
	MeteoCoolTime -= _DeltaTime;
	UpdateMapPattern(_DeltaTime);
	FSM.Update(_DeltaTime);

}

void ADunkel_Boss::StartSpawn()
{

	SpriteRenderer->ChangeAnimation("Spawn", true);
	SpriteRenderer->SetRelativeLocation(FVector(-20.0f, 200.0f, UContentsConst::BOSS_ZPOS));
}

void ADunkel_Boss::UpdateSpawn(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(EDunkelAnim_State::Stand);
		return;
	}
}

void ADunkel_Boss::StartStand()
{
	SpriteRenderer->ChangeAnimation("Stand");
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 180.0f, UContentsConst::BOSS_ZPOS));
	GetCollision("Character")->SetActive(true);
	GetCollision("Character")->SetRelativeLocation(FVector(10.0f, 170.0f));
	StandTime = 2.0f;
	CollisonSpawnTime = 0.0f;
	bIsAttacking = false;
}

void ADunkel_Boss::UpdateStand(float _DeltaTime)
{
	if (IsDebug()) 
	{
		return;
	}
	StandTime -= _DeltaTime;
	if (StandTime < 0.0f)
	{
		// 주변에 플레이어가 없을때
		if (!bIsScopePlayer)
		{
			if (SwordCoolTime < 0.0f)
			{
				FSM.ChangeState(EDunkelAnim_State::Sword);
				return;
			}
			if (SlashCoolTime < 0.0f)
			{

				FSM.ChangeState(EDunkelAnim_State::Slash_Start);
				return;
			}
			int Num = Random.RandomInt(0, 9);
			if (Num == 0 || Num == 2)
			{
				FSM.ChangeState(EDunkelAnim_State::Up);
				return;
			}
			else
			{
				FSM.ChangeState(EDunkelAnim_State::Knockback);
				return;
			}
		}
		// 주변에 플레이어가 있을때
		else
		{
			if (SlashCoolTime < 0.0f)
			{
				FSM.ChangeState(EDunkelAnim_State::Slash_Start);
				return;
			}
			if (MeteoCoolTime < 0.0f)
			{
				FSM.ChangeState(EDunkelAnim_State::Meteo);
				return;
			}
			int Num = Random.RandomInt(0, 9);
			if (Num == 0 || Num == 1)
			{
				FSM.ChangeState(EDunkelAnim_State::Force);
				return;
			}

			else
			{
				FSM.ChangeState(EDunkelAnim_State::Knockback);
				return;
			}
		}

	}

}
void ADunkel_Boss::CheckDir()
{
	float PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation().X;
	float MyPos = GetActorLocation().X;
	if (PlayerPos > MyPos) {
		Dir = -1;
	}
	else {
		Dir = 1;
	}
	SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));
}

void ADunkel_Boss::SpawnEliteMonster()
{
	int Count = 2;
	if (HpPercent < 0.51)
	{
		Count = 3;
	}

	std::shuffle(EliteMonsterList.begin(), EliteMonsterList.end(), Random.GetMtGen());
	for (int i = 0; i < Count; i++)
	{
		int Num = EliteMonsterList[i];
		switch (Num)
		{
		case 0:
			GetWorld()->SpawnActor<ACQ57>();
			break;
		case 1:
			GetWorld()->SpawnActor<AFreyd>();
			break;
		case 2:
			GetWorld()->SpawnActor<AJurai>();
			break;
		case 3:
			GetWorld()->SpawnActor<AKhaliain>();
			break;
		case 4:
			GetWorld()->SpawnActor<AMogadin>();
			break;
		}
	}

}



void ADunkel_Boss::StartDie()
{
	CheckDir();
	SpriteRenderer->ChangeAnimation("Die", true);
	SpriteRenderer->SetRelativeLocation(FVector(-60.0f, 180.0f, UContentsConst::BOSS_ZPOS));
	GetCollision("Character")->SetActive(false);
}

void ADunkel_Boss::UpdateDie(float _DeltaTime)
{

}



void ADunkel_Boss::StartKnockback()
{
	CheckDir();
	SpawnEliteMonster();
	SpriteRenderer->ChangeAnimation("Knockback", true);
	SpriteRenderer->SetRelativeLocation(FVector(-210.0f, 200.0f, UContentsConst::BOSS_ZPOS));
}

void ADunkel_Boss::UpdateKnockback(float _DeltaTime)
{
	CollisonSpawnTime += _DeltaTime;
	if (!bIsAttacking)
	{
		if (CollisonSpawnTime > 2.1f) {
			GetCollision("Knockback")->SetActive(true);
			bIsAttacking = true;
		}
	}
	if (CollisonSpawnTime > 2.3f) {
		GetCollision("Knockback")->SetActive(false);
	}
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(EDunkelAnim_State::Stand);
		return;
	}
}
void ADunkel_Boss::StartForce()
{
	CheckDir();
	SpawnEliteMonster();
	SpriteRenderer->ChangeAnimation("Force", true);
	SpriteRenderer->SetRelativeLocation(FVector(-120.0f, 360.0f, UContentsConst::BOSS_ZPOS));
}

void ADunkel_Boss::UpdateForce(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(EDunkelAnim_State::Stand);
		return;
	}
}


void ADunkel_Boss::StartMeteo()
{
	CheckDir();
	SpawnEliteMonster();
	MeteoCoolTime = 25.0f;
	SpriteRenderer->ChangeAnimation("Meteo", true);
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 320.0f, UContentsConst::BOSS_ZPOS));
	SpawnMeteo();
}

void ADunkel_Boss::UpdateMeteo(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(EDunkelAnim_State::Stand);
		return;
	}
}

void ADunkel_Boss::SpawnMeteo()
{
	FVector DunkelPos = GetActorLocation();
	float Dir = 1.0f;
	if (DunkelPos.X < 0)
	{
		Dir = 1.0f;
	}
	else
	{
		Dir = -1.0f;
	}

	{
		ADunkel_Meteo* Meteo = GetWorld()->SpawnActor<ADunkel_Meteo>().get();
		Meteo->SetDir(Dir);
		Meteo->SetStartPos(FVector(DunkelPos.X + (Dir * 1200.0f), 600.0f));
	}
	{
		ADunkel_Meteo* Meteo = GetWorld()->SpawnActor<ADunkel_Meteo>().get();
		Meteo->SetDir(Dir);
		Meteo->SetStartPos(FVector(DunkelPos.X + (Dir * 900.0f), 500.0f));
	}
	{
		ADunkel_Meteo* Meteo = GetWorld()->SpawnActor<ADunkel_Meteo>().get();
		Meteo->SetDir(Dir);
		Meteo->SetStartPos(FVector(DunkelPos.X + (Dir * 600.0f), 600.0f));
	}
	{
		ADunkel_Meteo* Meteo = GetWorld()->SpawnActor<ADunkel_Meteo>().get();
		Meteo->SetDir(Dir);
		Meteo->SetStartPos(FVector(DunkelPos.X + (Dir * 00.0f), 500.0f));
	}

}

void ADunkel_Boss::StartSlash_Start()
{
	CheckDir();
	SpawnEliteMonster();
	SpriteRenderer->ChangeAnimation("Slash_Start", true);
	SpriteRenderer->SetRelativeLocation(FVector(-60.0f, 170.0f, UContentsConst::BOSS_ZPOS));
	SlashCoolTime = 15.0f;
}

void ADunkel_Boss::UpdateSlash_Start(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(EDunkelAnim_State::Slash_End);
		return;
	}
}

void ADunkel_Boss::StartSlash_End()
{

	SpriteRenderer->ChangeAnimation("Slash_End", true);
	SpriteRenderer->SetRelativeLocation(FVector(200.0f, 240.0f, UContentsConst::BOSS_ZPOS));
	AddActorLocation(FVector(-Dir * 500, 0.0f));
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
		FSM.ChangeState(EDunkelAnim_State::Stand);
		return;
	}
}




void ADunkel_Boss::StartSword()
{
	CheckDir();
	SpawnEliteMonster();
	SpriteRenderer->ChangeAnimation("Sword", true);
	SpriteRenderer->SetRelativeLocation(FVector(60.0f, 200.0f, UContentsConst::BOSS_ZPOS));
	SwordCoolTime = 30.0f;
	SpawnSwordPower();

}

void ADunkel_Boss::UpdateSword(float _DeltaTime)
{

	if (SpriteRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(EDunkelAnim_State::Stand);
		return;
	}
}

void ADunkel_Boss::SpawnSwordPower()
{
	CheckDir();
	ADunkel_SwordPower* Power = GetWorld()->SpawnActor<ADunkel_SwordPower>().get();
	Power->SetDir(Dir);
	Power->SetStartPos(GetActorLocation() + FVector(-Dir * 330, 0.0f));
}

void ADunkel_Boss::StartUp()
{
	SpawnEliteMonster();
	SpriteRenderer->ChangeAnimation("Up", true);
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 180.0f, UContentsConst::BOSS_ZPOS));
	GetCollision("Character")->SetActive(false);
}

void ADunkel_Boss::UpdateUp(float _DeltaTime)
{
	if (SpriteRenderer->IsCurAnimationEnd())
	{
		FSM.ChangeState(EDunkelAnim_State::Down);
		return;
	}
}

void ADunkel_Boss::StartDown()
{
	CheckDir();
	SpriteRenderer->ChangeAnimation("Down", true);
	SpriteRenderer->SetRelativeLocation(FVector(-50.0f, 400.0f, UContentsConst::BOSS_ZPOS));
	GetCollision("Character")->SetActive(true);
	GetCollision("Down")->SetActive(true);
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
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
		FSM.ChangeState(EDunkelAnim_State::Stand);
		return;
	}
}


void ADunkel_Boss::UpdateMapPattern(float _DeltaTime)
{
	FallenWarriorSpawnTime -= _DeltaTime;
	PillarLightSpawnTime -= _DeltaTime;

	// FallenWarrior
	if (FallenWarriorSpawnTime <= 0.0f)
	{
		std::shuffle(FallenWarriorSpawnPosX.begin(), FallenWarriorSpawnPosX.end(), Random.GetMtGen());
		for (int i = 0; i < 4; i++) {
			AFallenWarrior* FallenWarrior = GetWorld()->SpawnActor<AFallenWarrior>().get();
			FallenWarrior->SetActorLocation(FVector(FallenWarriorSpawnPosX[i], 0.0f));	
		}
		FallenWarriorSpawnTime = 30.0f;
	}

	// PillarLight
	if (PillarLightSpawnTime <= 0.0f) {
		int Index = Random.RandomInt(0, PillarLightPosX.size() - 1);
		if (PillarLightSpawnCount < 3)
		{
			if (PillarLightCount < 4)
			{
				APillarLight* PillarLight = GetWorld()->SpawnActor<APillarLight>().get();
				PillarLight->SetActorLocation(FVector(PillarLightPosX[Index], 0.0f));
				PillarLightCount++;
				PillarLightSpawnTime = 1.0f;
			}
			else
			{
				PillarLightCount = 0;
				PillarLightSpawnCount++;
				PillarLightSpawnTime = 10.0f;
			}
		}
		else
		{
			PillarLightCount = 0;
			PillarLightSpawnCount = 0;
			PillarLightSpawnTime = 20.0f;
		}
	}
}
