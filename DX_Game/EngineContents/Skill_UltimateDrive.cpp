#include "PreCompile.h"
#include "Skill_UltimateDrive.h"
#include "Player.h"
#include "PlayerFuncManager.h"


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

	Collision = CreateDefaultSubObject<UCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("PlayerSkill");
	Collision->SetScale3D(FVector(340.0f, 300.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-180.0f, 50.0f));

	FrameState.CreateState(Skill_Frame::First, std::bind(&ASkill_UltimateDrive::UpdateUltimateDrivePrev, this, std::placeholders::_1), std::bind(&ASkill_UltimateDrive::StartUltimateDrivePrev, this));
	FrameState.CreateState(Skill_Frame::Second, std::bind(&ASkill_UltimateDrive::UpdateUltimateDriveKeyDown, this, std::placeholders::_1), std::bind(&ASkill_UltimateDrive::StartUltimateDriveKeyDown, this));
	FrameState.CreateState(Skill_Frame::Third, std::bind(&ASkill_UltimateDrive::UpdateUltimateDriveEnd, this, std::placeholders::_1), std::bind(&ASkill_UltimateDrive::StartUltimateDriveEnd, this));
}

ASkill_UltimateDrive::~ASkill_UltimateDrive()
{

}

void ASkill_UltimateDrive::SetActiveTrue()
{
	ASkill::SetActiveTrue();
	Key = Player->GetPlayerFuncManager()->GetKey("UltimateDrive");
	ChangeState(Skill_Frame::First);
}

void ASkill_UltimateDrive::StartUltimateDrivePrev()
{
	if (!PlayerLogic->bIsSkillable||!PlayerLogic->bIsGround)
	{
		SetActiveFalse();
		return;
	}
	Collision->SetActive(false);
	PlayerLogic->bIsUsingSkill =true;
	PlayerLogic->bIsSkillable = false;
	PlayerLogic->bIsJumpable = false;
	Player->ChangeAnimation("UltimateDrive_KeyDown");
	SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_Start_Effect_Front",true);
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(-100.0f, 50.0f, static_cast<float>(Z_ORDER::Skill_Front)));
	SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_Start_Effect_Back", true);
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(50.0f, 50.0f, static_cast<float>(Z_ORDER::Skill_Back)));
}

void ASkill_UltimateDrive::UpdateUltimateDrivePrev(float _DeltaTime)
{
	if (UEngineInput::IsUp(Key)||UEngineInput::IsFree(Key)) {
		FrameState.ChangeState(Skill_Frame::Third);
		return;
	}
	if (SpriteRenderers["Front"]->IsCurAnimationEnd())
	{
		FrameState.ChangeState(Skill_Frame::Second);
		return;
	}
}

void ASkill_UltimateDrive::StartUltimateDriveKeyDown()
{
	Collision->SetActive(true);
	SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Front");
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(-140.0f, 70.0f, static_cast<float>(Z_ORDER::Skill_Front)));
	SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Back");
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(100.0f, 100.0f, static_cast<float>(Z_ORDER::Skill_Back)));

}

void ASkill_UltimateDrive::UpdateUltimateDriveKeyDown(float _DeltaTime)
{
	if (UEngineInput::IsUp(Key)||UEngineInput::IsFree(Key)) {
		FrameState.ChangeState(Skill_Frame::Third);
		return;
	}
}

void ASkill_UltimateDrive::StartUltimateDriveEnd()
{
	Collision->SetActive(false);
	PlayerLogic->bIsSkillable = true;
	PlayerLogic->bIsUsingSkill = false;
	PlayerLogic->bIsJumpable = true;
	SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_End_Effect_Front",true);
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(-100.0f, 50.0f, static_cast<float>(Z_ORDER::Skill_Front)));
	SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_End_Effect_Back", true);
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(50.0f, 50.0f, static_cast<float>(Z_ORDER::Skill_Back)));
}

void ASkill_UltimateDrive::UpdateUltimateDriveEnd(float _DeltaTime)
{
	if (UEngineInput::IsDown(Key) || UEngineInput::IsPress(Key))
	{
		FrameState.ChangeState(Skill_Frame::First);
		return;
	}
	if (SpriteRenderers["Front"]->IsCurAnimationEnd()) {
		SetActiveFalse();
		return;
	}
}
