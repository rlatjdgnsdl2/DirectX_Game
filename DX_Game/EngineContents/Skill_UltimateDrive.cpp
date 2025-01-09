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




		SpriteRenderer->AddZ(static_cast<float>(Z_ORDER::Skill_Front));
		SpriteRenderer->ChangeAnimation("UltimateDrive_KeyDown_Effect_Front");

		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer));
	}

	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("UltimateDrive_Start_Effect_Back", "UltimateDrive_Start_Effect_Back", 0, 4, 0.05f);
		SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown_Effect_Back", "UltimateDrive_KeyDown_Effect_Back", 0, 5, 0.05f);
		SpriteRenderer->CreateAnimation("UltimateDrive_End_Effect_Back", "UltimateDrive_End_Effect_Back", 0, 4, 0.05f);

		SpriteRenderer->SetLoopValue("UltimateDrive_Start_Effect_Back", false);
		SpriteRenderer->SetLoopValue("UltimateDrive_End_Effect_Back", false);


		SpriteRenderer->AddZ(static_cast<float>(Z_ORDER::Skill_Back));
		SpriteRenderer->AddRelativeLocation(FVector(250.0f, 100.0f, 0.0f));
		SpriteRenderers.insert(std::make_pair("Back", SpriteRenderer));
	}

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("PlayerSkill");
	Collision->SetScale3D(FVector(400.0f, 300.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-200.0f,50.0f));
	Collision->SetActive(false);


	




	FrameState.CreateState(Skill_Frame::Start, [this](float _DeltaTime)
		{
			APlayer* Player = dynamic_cast<APlayer*>(Owner);
			Key = Player->GetPlayerFuncManager()->GetKey("UltimateDrive");
			if (UEngineInput::IsFree(Key)) {
				Collision->SetActive(false);
				FrameState.ChangeState(Skill_Frame::End);
			}
			if (UEngineInput::IsPressTime(Key) >= 0.2f)
			{
				FrameState.ChangeState(Skill_Frame::KeyDown);
				Collision->SetActive(true);
			}
		},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_Start_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(70.0f, -30.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_Start_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(80.0f, -20.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});
	FrameState.CreateState(Skill_Frame::KeyDown, [this](float _DeltaTime)
		{
			if (UEngineInput::IsFree(Key)) {
				Collision->SetActive(false);
				FrameState.ChangeState(Skill_Frame::End);
			}
		},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(-130.0f, -150.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(100.0f, -55.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});

	FrameState.CreateState(Skill_Frame::End, [this](float _DeltaTime)
		{
			if (SpriteRenderers["Front"]->IsCurAnimationEnd()) {
				APlayer* Player = dynamic_cast<APlayer*>(Owner);
				Player->SetSkill(false);
				Player->SetJumpAble(true);
				SetActiveFalse();
			}
		},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_End_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(-130.0f, -150.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_End_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(100.0f, -55.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});

}

ASkill_UltimateDrive::~ASkill_UltimateDrive()
{

}

void ASkill_UltimateDrive::BeginPlay()
{
	ASkill::BeginPlay();
	FrameState.ChangeState(Skill_Frame::Start);
}

void ASkill_UltimateDrive::Tick(float _DeltaTime)
{
	ASkill::Tick(_DeltaTime);
	FrameState.Update(_DeltaTime);
}
