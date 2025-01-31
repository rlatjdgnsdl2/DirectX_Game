#include "PreCompile.h"
#include "Dunkel_Meteo.h"


ADunkel_Meteo::ADunkel_Meteo()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->AddRelativeLocation(FVector(0.0f, 50.0f));
	SpriteRenderer->CreateAnimation("Meteo_Start", "Dunkel_Meteo_Effect_Start", 0, 11, 1.0f / 12, false);
	SpriteRenderer->CreateAnimation("Meteo_Update", "Dunkel_Meteo_Effect_Update", 0, 15, 1.0f / 16);
	SpriteRenderer->CreateAnimation("Meteo_End", "Dunkel_Meteo_Effect_End", 0, 5, 1.0f / 6, false);
	SpriteRenderer->ChangeAnimation("Meteo_End");

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("BossAttack");
	Collision->SetRelativeScale3D(FVector(170.0f, 170.0f, 1.0f));
	Collision->AddRelativeLocation(FVector(0.0f, 50.0f));
	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			if (_Right->GetCollisionProfileName() == "PLAYER")
			{
				GetGameInstance<MyGameInstance>()->PlayerStatus.TakeHpPercentDamage(0.4f);
				Collision->SetActive(false);
				AnimaionFSM.ChangeState(ESkill_Frame::Third);
				return;
			}
			
		});

	AnimaionFSM.CreateState(ESkill_Frame::First, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(ESkill_Frame::Second);
				return;
			}

		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Meteo_Start");
			SetActorLocation(StartPos);
			SetActorRelativeScale3D(FVector(Dir, 1.0f, 1.0f));
		});
	AnimaionFSM.CreateState(ESkill_Frame::Second, [this](float _DeltaTime)
		{
			AddActorLocation(FVector(-Dir*50.0f * _DeltaTime, -25.0f * _DeltaTime, 0.0f));
			if(GetActorLocation().Y <=0.0f)
			{
				AnimaionFSM.ChangeState(ESkill_Frame::Third);
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Meteo_Update");
		});
	AnimaionFSM.CreateState(ESkill_Frame::Third, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				Destroy();
				return;
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Meteo_End");
		});
	

}

ADunkel_Meteo::~ADunkel_Meteo()
{

}

void ADunkel_Meteo::BeginPlay()
{
	AActor::BeginPlay();
	AnimaionFSM.ChangeState(ESkill_Frame::First);
}

void ADunkel_Meteo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AnimaionFSM.Update(_DeltaTime);
}
