#include "PreCompile.h"
#include "Dunkel_Boss.h"


ADunkel_Boss::ADunkel_Boss() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->AddZ(static_cast<float>(Z_ORDER::Boss));
	
	SpriteRenderer->CreateAnimation("Spawn", "Dunkel_Spawn", 0, 31, 0.1f, false);
	SpriteRenderer->CreateAnimation("Stand", "Dunkel_Stand", 0, 12);
	SpriteRenderer->CreateAnimation("Knockback", "Dunkel_Knockback", 0, 29);

	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetActive(false);
		Collision->SetRelativeScale3D(FVector(400.0f,300.0f,100.0f));
		Collision->SetRelativeLocation(FVector(-200.0f, 0.0f, 0.0f));
		Collision->SetCollisionProfileName("BossAttack");	
		AttackCollisionMap.insert(std::make_pair("Knockback", Collision));
	}

	
	AnimaionFSM.CreateState(DunkelAnim_State::Spawn, [this](float _DeltaTime) 
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Spawn",true);
			SpriteRenderer->SetRelativeLocation(FVector(20.0f,30.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(false);
			
		});

	AnimaionFSM.CreateState(DunkelAnim_State::Stand, nullptr,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Stand");
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 0.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(true);
			Collision->SetRelativeLocation(FVector(50.0f, 10.0f));
		});

	AnimaionFSM.CreateState(DunkelAnim_State::Knockback, [this](float _DeltaTime) 
		{
			CurTime += _DeltaTime;
			if (CurTime>1.7f) {
				AttackCollisionMap["Knockback"]->SetActive(true);
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
			SpriteRenderer->SetRelativeLocation(FVector(-180.0f, 20.0f, static_cast<float>(Z_ORDER::Boss)));
			Collision->SetActive(true);
		});

	

	
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Boss");
	Collision->SetRelativeScale3D(FVector(150.0f, 280.0f, 1.0f));
	

}

ADunkel_Boss::~ADunkel_Boss() 
{

}

void ADunkel_Boss::BeginPlay()
{
	AActor::BeginPlay();
	AnimaionFSM.ChangeState(DunkelAnim_State::Spawn);
	AddActorLocation(FVector(0.0f, -160.0f));

}

void ADunkel_Boss::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AnimaionFSM.Update(_DeltaTime);

	if (UEngineInput::IsDown('1')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Spawn);
	}
	if (UEngineInput::IsDown('2')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
	}
	if (UEngineInput::IsDown('3')) {
		AnimaionFSM.ChangeState(DunkelAnim_State::Knockback);
	}
}
