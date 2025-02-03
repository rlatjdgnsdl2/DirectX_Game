#include "PreCompile.h"
#include "Skill_DefyingFate.h"
#include "Player.h"

#include "Monster.h"
#include "DamageSkinFactory.h"



ASkill_DefyingFate::ASkill_DefyingFate()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("DefyingFate_Start", "DefyingFate_Start", 0, 56, 0.05f, false);
		SpriteRenderer->CreateAnimation("DefyingFate_Update", "DefyingFate_Update", 0, 15, 0.1f);
		SpriteRenderer->CreateAnimation("DefyingFate_End", "DefyingFate_End", 0, 13, 0.1f, false);
		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer));
	}

	FSM.CreateState(ESkill_Frame::First, std::bind(&ASkill_DefyingFate::Update_DefyingFate_Start, this, std::placeholders::_1), std::bind(&ASkill_DefyingFate::Start_DefyingFate_Start, this));
	FSM.CreateState(ESkill_Frame::Second, std::bind(&ASkill_DefyingFate::Update_DefyingFate_Update, this, std::placeholders::_1), std::bind(&ASkill_DefyingFate::Start_DefyingFate_Update, this));
	FSM.CreateState(ESkill_Frame::Third, std::bind(&ASkill_DefyingFate::Update_DefyingFate_End, this, std::placeholders::_1), std::bind(&ASkill_DefyingFate::Start_DefyingFate_End, this));

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("PlayerSkill");
	FVector Size = UEngineCore::GetScreenScale();
	Collision->SetRelativeScale3D(Size);
	Collision->SetCollisionEnter([this](UCollision* _Left, UCollision* _Right)
		{
			AMonster* Monster = dynamic_cast<AMonster*>(_Right->GetActor());
			if (Monster == nullptr)
			{
				return;
			}
			ADamageSkinFactory* Factory = GetWorld()->SpawnActor<ADamageSkinFactory>().get();
			Factory->SetMonsterCollision(_Right);
			Factory->SetDamageInfo(DamageInfo);
			Monster->SetDamage(DamageInfo.Damage * DamageInfo.MaxHitCount * DamageInfo.MaxHitCycle);
		});


	DamageInfo.Damage = 999999999;
	DamageInfo.HitDelay = 0.05f;
	DamageInfo.MaxHitCount = 11;
	DamageInfo.MaxHitCycle = 3;



}

ASkill_DefyingFate::~ASkill_DefyingFate()
{

}

void ASkill_DefyingFate::Start_DefyingFate_Start()
{
	SpriteRenderers["Front"]->ChangeAnimation("DefyingFate_Start");
	Collision->SetActive(true);

}

void ASkill_DefyingFate::Update_DefyingFate_Start(float _DeltaTime)
{
	FVector Pos = GetWorld()->GetMainCamera()->GetActorLocation();
	SetActorLocation(FVector(Pos.X, Pos.Y, UContentsConst::P_EFFECT_FRONT_ZPOS));
	if (SpriteRenderers["Front"]->IsCurAnimationEnd())
	{
		FSM.ChangeState(ESkill_Frame::Second);
	}
}

void ASkill_DefyingFate::Start_DefyingFate_Update()
{
	SpriteRenderers["Front"]->ChangeAnimation("DefyingFate_Update");
	Player->ChangeState(EPlayer_State::Idle);
}

void ASkill_DefyingFate::Update_DefyingFate_Update(float _DeltaTime)
{
	CurTime += _DeltaTime;
	FVector Pos = GetWorld()->GetMainCamera()->GetActorLocation();
	SetActorLocation(FVector(Pos.X, Pos.Y, UContentsConst::SKILL_COVER_ZPOS));
	if (CurTime >= 30.0f)
	{
		FSM.ChangeState(ESkill_Frame::Third);
	}
}

void ASkill_DefyingFate::Start_DefyingFate_End()
{
	SpriteRenderers["Front"]->ChangeAnimation("DefyingFate_End");

}

void ASkill_DefyingFate::Update_DefyingFate_End(float _DeltaTime)
{
	FVector Pos = GetWorld()->GetMainCamera()->GetActorLocation();
	SetActorLocation(FVector(Pos.X, Pos.Y, UContentsConst::SKILL_COVER_ZPOS));
	if (SpriteRenderers["Front"]->IsCurAnimationEnd())
	{
		SetActiveFalse();
	}
}

void ASkill_DefyingFate::BeginPlay()
{
	AActor::BeginPlay();
}

void ASkill_DefyingFate::Tick(float _DeltaTime)
{
	ASkill::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);

}

void ASkill_DefyingFate::SetActiveTrue()
{
	ASkill::SetActiveTrue();
	FSM.ChangeState(ESkill_Frame::First);
	CurTime = 0.0f;
}

void ASkill_DefyingFate::SetActiveFalse()
{
	ASkill::SetActiveFalse();
}
