#include "PreCompile.h"
#include "Skill_UltimateDrive.h"
#include "Player.h"
#include "PlayerFuncManager.h"

#include <EngineCore/EngineCore.h>
#include "MyCollision.h"
#include "DamageSkinFactory.h"
#include "Monster.h"
#include "MyGameInstance.h"


ASkill_UltimateDrive::ASkill_UltimateDrive()
{

	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("UltimateDrive_Start_Effect_Front", "UltimateDrive_Start_Effect_Front", 0, 4, 0.05f, false);
		SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown_Effect_Front", "UltimateDrive_KeyDown_Effect_Front", 0, 5, 0.05f);
		SpriteRenderer->CreateAnimation("UltimateDrive_End_Effect_Front", "UltimateDrive_End_Effect_Front", 0, 4, 0.05f, false);

		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer.get()));
	}

	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("UltimateDrive_Start_Effect_Back", "UltimateDrive_Start_Effect_Back", 0, 4, 0.05f, false);
		SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown_Effect_Back", "UltimateDrive_KeyDown_Effect_Back", 0, 5, 0.05f);
		SpriteRenderer->CreateAnimation("UltimateDrive_End_Effect_Back", "UltimateDrive_End_Effect_Back", 0, 4, 0.05f, false);

		SpriteRenderers.insert(std::make_pair("Back", SpriteRenderer.get()));
	}

	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("PlayerSkill");
	Collision->SetScale3D(FVector(340.0f, 300.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-180.0f, 50.0f));
	Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
		{
			DelayTime -= GetDeltaTime();
			if (DelayTime < 0.0f)
			{
				AMonster* Monster = dynamic_cast<AMonster*>(_Right->GetActor());
				if (Monster == nullptr)
				{
					return;
				}
				ADamageSkinFactory* Factory = GetWorld()->SpawnActor<ADamageSkinFactory>().get();
				Factory->SetDamageInfo(DamageInfo);
				Factory->SetMonsterCollision(_Right);
				DelayTime = 0.3f;
			}
		});


	FSM.CreateState(ESkill_Frame::First, std::bind(&ASkill_UltimateDrive::UpdateUltimateDrivePrev, this, std::placeholders::_1), std::bind(&ASkill_UltimateDrive::StartUltimateDrivePrev, this));
	FSM.CreateState(ESkill_Frame::Second, std::bind(&ASkill_UltimateDrive::UpdateUltimateDriveKeyDown, this, std::placeholders::_1), std::bind(&ASkill_UltimateDrive::StartUltimateDriveKeyDown, this));
	FSM.CreateState(ESkill_Frame::Third, std::bind(&ASkill_UltimateDrive::UpdateUltimateDriveEnd, this, std::placeholders::_1), std::bind(&ASkill_UltimateDrive::StartUltimateDriveEnd, this));

	DamageInfo.Damage = 999999999;
	DamageInfo.HitDelay = 0.1f;
	DamageInfo.MaxHitCount = 3;
	UseMp = 200.0f;
}

ASkill_UltimateDrive::~ASkill_UltimateDrive()
{

}

void ASkill_UltimateDrive::SetActiveTrue()
{
	ASkill::SetActiveTrue();
	Key = Player->GetPlayerFuncManager()->GetKey(EPlayer_Function::Ultimate_Drive);
	ChangeState(ESkill_Frame::First);
}

void ASkill_UltimateDrive::StartUltimateDrivePrev()
{
	DelayTime = 0.0f;
	Collision->SetActive(true);
	SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_Start_Effect_Front", true);
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(-100.0f, 50.0f, UContentsConst::P_EFFECT_FRONT_ZPOS));
	SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_Start_Effect_Back", true);
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(50.0f, 50.0f, UContentsConst::P_EFFECT_BACK_ZPOS));
}

void ASkill_UltimateDrive::UpdateUltimateDrivePrev(float _DeltaTime)
{
	if (UEngineInput::IsUp(Key) || UEngineInput::IsFree(Key)) {
		FSM.ChangeState(ESkill_Frame::Third);
		return;
	}
	if (SpriteRenderers["Front"]->IsCurAnimationEnd())
	{
		FSM.ChangeState(ESkill_Frame::Second);
		return;
	}
}

void ASkill_UltimateDrive::StartUltimateDriveKeyDown()
{
	SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Front");
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(-140.0f, 70.0f, UContentsConst::P_EFFECT_FRONT_ZPOS));
	SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Back");
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(100.0f, 100.0f, UContentsConst::P_EFFECT_BACK_ZPOS));
}

void ASkill_UltimateDrive::UpdateUltimateDriveKeyDown(float _DeltaTime)
{
	MpUseTime -= _DeltaTime;
	if (MpUseTime < 0.0f)
	{
		GetGameInstance<MyGameInstance>()->PlayerStatus.UseMp(UseMp);
		Collision->SetActive(true);
		MpUseTime = 0.3f;
	}
	if (UEngineInput::IsUp(Key) || UEngineInput::IsFree(Key)) {
		FSM.ChangeState(ESkill_Frame::Third);
		return;
	}
}

void ASkill_UltimateDrive::StartUltimateDriveEnd()
{
	Collision->SetActive(false);
	SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_End_Effect_Front", true);
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(-100.0f, 50.0f, UContentsConst::P_EFFECT_FRONT_ZPOS));
	SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_End_Effect_Back", true);
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(50.0f, 50.0f, UContentsConst::P_EFFECT_BACK_ZPOS));
}

void ASkill_UltimateDrive::UpdateUltimateDriveEnd(float _DeltaTime)
{
	if (UEngineInput::IsDown(Key) || UEngineInput::IsPress(Key))
	{
		FSM.ChangeState(ESkill_Frame::First);
		return;
	}
	if (SpriteRenderers["Front"]->IsCurAnimationEnd()) {
		SetActiveFalse();
		return;
	}
}
