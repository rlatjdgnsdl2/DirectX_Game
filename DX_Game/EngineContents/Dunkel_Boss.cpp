#include "PreCompile.h"
#include "Dunkel_Boss.h"
#include "Player.h"
#include "FallenWarrior.h"


ADunkel_Boss::ADunkel_Boss() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);
	
	SpriteRenderer->CreateAnimation("Die", "Dunkel_Die", 0, 27,0.1f,false);
	SpriteRenderer->CreateAnimation("Down", "Dunkel_Down", 0, 14, 0.1f, false);
	SpriteRenderer->CreateAnimation("Force", "Dunkel_Force", 0, 24, 0.1f, false);
	SpriteRenderer->CreateAnimation("Knockback", "Dunkel_Knockback", 0, 29,0.1f,false);
	SpriteRenderer->CreateAnimation("Meteo", "Dunkel_Meteo", 0, 23, 0.1f, false);
	SpriteRenderer->CreateAnimation("Slash_End", "Dunkel_Slash_End", 0, 15, 0.1f, false);
	SpriteRenderer->CreateAnimation("Slash_Start", "Dunkel_Slash_Start", 0, 10, 0.1f, false);
	SpriteRenderer->CreateAnimation("Spawn", "Dunkel_Spawn", 0, 31, 0.1f, false);
	SpriteRenderer->CreateAnimation("Stand", "Dunkel_Stand", 0, 12);
	SpriteRenderer->CreateAnimation("Sword", "Dunkel_SwordPower", 0, 19,0.1f,false);
	SpriteRenderer->CreateAnimation("Up", "Dunkel_Up", 0, 15, 0.1f, false);

	AnimaionFSM.CreateState(DunkelAnim_State::Die, [this](float _DeltaTime)
		{
			
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Die", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 300.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);

		});

	AnimaionFSM.CreateState(DunkelAnim_State::Down, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Down", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 500.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);

		});

	AnimaionFSM.CreateState(DunkelAnim_State::Force, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Force", true);
			SpriteRenderer->SetRelativeLocation(FVector(-80.0f, 470.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);
		});

	AnimaionFSM.CreateState(DunkelAnim_State::Knockback, [this](float _DeltaTime)
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
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Knockback");
			SpriteRenderer->SetRelativeLocation(FVector(-150.0f, 300.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(true);
		});


	AnimaionFSM.CreateState(DunkelAnim_State::Meteo, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Meteo", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 450.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);

		});


	
	AnimaionFSM.CreateState(DunkelAnim_State::Slash_End, [this](float _DeltaTime) 
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Slash_End",true);
			SpriteRenderer->SetRelativeLocation(FVector(180.0f,330.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);
			
		});

	AnimaionFSM.CreateState(DunkelAnim_State::Slash_Start, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Slash_End);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Slash_Start", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 300.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);

		});

	AnimaionFSM.CreateState(DunkelAnim_State::Spawn, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Spawn", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 300.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);

		});

	AnimaionFSM.CreateState(DunkelAnim_State::Stand, nullptr,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Stand");
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 300.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(true);
			Collision->SetRelativeLocation(FVector(50.0f, 300.0f));
		});

	AnimaionFSM.CreateState(DunkelAnim_State::Sword, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Sword", true);
			SpriteRenderer->SetRelativeLocation(FVector(120.0f, 300.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);
		});
	AnimaionFSM.CreateState(DunkelAnim_State::Up, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Down);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Up", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 300.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);
		});

	
	

	//	���� �ݸ���
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Boss");
	Collision->SetRelativeScale3D(FVector(150.0f, 280.0f, 1.0f));
	// �������� �ݸ���
	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetActive(false);
		Collision->SetRelativeScale3D(FVector(400.0f, 300.0f, 100.0f));
		Collision->SetRelativeLocation(FVector(-200.0f, 300.0f, 0.0f));
		Collision->SetCollisionProfileName("BossAttack");
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				float Dir = GetActorTransform().Scale.X;
				Player->SetVelocityX(-Dir * 1000.0f);
				Player->SetVelocityY(1000.0f);
				Player->SetGravityAccel(0.0f);
				Player->GetBoolValue().IsJumpAbleValue = false;
				Player->SetDownableFloor(false);
			});
		AttackCollisionMap.insert(std::make_pair("Knockback", Collision));
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
		AnimaionFSM.ChangeState(DunkelAnim_State::Down);
	}
	if (UEngineInput::IsDown('3')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Force);
	}
	if (UEngineInput::IsDown('4')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Knockback);
	}
	if (UEngineInput::IsDown('5')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Meteo);
	}
	if (UEngineInput::IsDown('6')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Slash_End);
	}
	if (UEngineInput::IsDown('7')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Slash_Start);
	}
	if (UEngineInput::IsDown('8')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Spawn);
	}
	if (UEngineInput::IsDown('9')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
	}

	if (UEngineInput::IsDown('0')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Sword);
	}
	if (UEngineInput::IsDown(VK_F1)) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Up);
	}


	
}
