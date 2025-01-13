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

		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer));
	}

	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("UltimateDrive_Start_Effect_Back", "UltimateDrive_Start_Effect_Back", 0, 4, 0.05f, false);
		SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown_Effect_Back", "UltimateDrive_KeyDown_Effect_Back", 0, 5, 0.05f);
		SpriteRenderer->CreateAnimation("UltimateDrive_End_Effect_Back", "UltimateDrive_End_Effect_Back", 0, 4, 0.05f, false);

		SpriteRenderers.insert(std::make_pair("Back", SpriteRenderer));
	}

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("PlayerSkill");
	Collision->SetScale3D(FVector(400.0f, 300.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-200.0f, 50.0f));
	Collision->SetActive(false);

	FrameState.CreateState(Skill_Frame::Start, [this](float _DeltaTime)
		{
			Key = Player->GetPlayerFuncManager()->GetKey("UltimateDrive");
			if (UEngineInput::IsFree(Key)) {
				Collision->SetActive(false);
				FrameState.ChangeState(Skill_Frame::End);
			}
			if (UEngineInput::GetPressTime(Key) >= 0.2f)
			{
				FrameState.ChangeState(Skill_Frame::Update);
				Collision->SetActive(true);
			}
		},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_Start_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(-100.0f, 50.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_Start_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(50.0f, 50.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});
	FrameState.CreateState(Skill_Frame::Update, [this](float _DeltaTime)
		{
			if (UEngineInput::IsFree(Key)) {
				Collision->SetActive(false);
				FrameState.ChangeState(Skill_Frame::End);
			}
		},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(-140.0f, 70.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(100.0f, 100.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});

	FrameState.CreateState(Skill_Frame::End, [this](float _DeltaTime)
		{
			if (SpriteRenderers["Front"]->IsCurAnimationEnd()) {
				Player->GetBoolValue().IsUsingSkillValue = false;
				Player->GetBoolValue().IsJumpAbleValue = true;
				SetActiveFalse();
			}
		},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_End_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(-100.0f, 50.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_End_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(50.0f, 50.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});

}

ASkill_UltimateDrive::~ASkill_UltimateDrive()
{

}

void ASkill_UltimateDrive::BeginPlay()
{
	ASkill::BeginPlay();
}

void ASkill_UltimateDrive::Tick(float _DeltaTime)
{
	ASkill::Tick(_DeltaTime);
	
}

void ASkill_UltimateDrive::SetActiveTrue()
{
	ASkill::SetActiveTrue();
	Player = dynamic_cast<APlayer*>(Owner);
	Key = Player->GetPlayerFuncManager()->GetKey("UltimateDrive");
	ChangeState(Skill_Frame::Start);
}
