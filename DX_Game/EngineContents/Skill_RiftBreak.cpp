#include "PreCompile.h"
#include "Skill_RiftBreak.h"
#include "Player.h"
#include "PlayerFuncManager.h"

#include "Monster.h"
#include "DamageSkinFactory.h"


ASkill_RiftBreak::ASkill_RiftBreak()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("RiftBreak_Front_Effect", "RiftBreak_Front_Effect", 0, 17, 0.05f, false);

		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer));
	}
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("RiftBreak_Back_Effect", "RiftBreak_Back_Effect", 0, 13, 0.05f, false);
		SpriteRenderers.insert(std::make_pair("Back", SpriteRenderer));
	}

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("PlayerSkill");
	Collision->SetScale3D(FVector(350.0f, 200.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-180.0f, 70.0f));
	Collision->SetCollisionEnter([this](UCollision* _Left, UCollision* _Right)
		{
			AMonster* Monster = dynamic_cast<AMonster*>(_Right->GetActor());
			if (Monster == nullptr)
			{
				return;
			}
			if (Monster->IsDamagedable())
			{
				ADamageSkinFactory* Factory = GetWorld()->SpawnActor<ADamageSkinFactory>().get();
				Factory->SetDamageInfo(DamageInfo);
				Factory->SetSpawnLocation(_Right->GetWorldLocation() + FVector(0.0f, std::abs(_Right->GetWorldScale3D().hY())));
				Monster->SetDamage(DamageInfo.Damage * DamageInfo.MaxHitCount);

			}
			else
			{
				ADamageSkinFactory* Factory = GetWorld()->SpawnActor<ADamageSkinFactory>().get();
				FDamageInfo DamageInfo;
				DamageInfo.Damage = 0.0f;
				DamageInfo.HitDelay = 0.1f;
				DamageInfo.MaxHitCount = 3;
				Factory->SetDamageInfo(DamageInfo);
				Factory->SetSpawnLocation(_Right->GetWorldLocation() + FVector(0.0f, std::abs(_Right->GetWorldScale3D().hY())));
			}

		});

	FSM.CreateState(ESkill_Frame::First, std::bind(&ASkill_RiftBreak::UpdateRiftBreak, this, std::placeholders::_1), std::bind(&ASkill_RiftBreak::StartRiftBreak, this));

	DamageInfo.Damage = 999999999;
	DamageInfo.HitDelay = 0.1f;
	DamageInfo.MaxHitCount = 10;

}

ASkill_RiftBreak::~ASkill_RiftBreak()
{

}

void ASkill_RiftBreak::StartRiftBreak()
{
	SpriteRenderers["Front"]->ChangeAnimation("RiftBreak_Front_Effect", true);
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(-150.0f, 100.0f, UContentsConst::P_EFFECT_FRONT_ZPOS));
	SpriteRenderers["Back"]->ChangeAnimation("RiftBreak_Back_Effect", true);
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(-150.0f, 100.0f, UContentsConst::P_EFFECT_FRONT_ZPOS + 50.0f));
}

void ASkill_RiftBreak::UpdateRiftBreak(float _DeltaTime)
{
	if (SpriteRenderers["Back"]->IsCurAnimationEnd())
	{
		SetActiveFalse();
	}
}

void ASkill_RiftBreak::BeginPlay()
{
	ASkill::BeginPlay();
	FSM.ChangeState(ESkill_Frame::First);
}

void ASkill_RiftBreak::Tick(float _DeltaTime)
{
	ASkill::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void ASkill_RiftBreak::SetActiveTrue()
{
	ASkill::SetActiveTrue();
	Key = Player->GetPlayerFuncManager()->GetKey(EPlayer_Function::Rift_Break);
	FSM.ChangeState(ESkill_Frame::First);
}

void ASkill_RiftBreak::SetActiveFalse()
{
	ASkill::SetActiveFalse();
}
