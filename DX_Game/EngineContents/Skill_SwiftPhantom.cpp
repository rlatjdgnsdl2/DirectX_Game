#include "PreCompile.h"
#include "Skill_SwiftPhantom.h"

#include "Player.h"
#include "PlayerFuncManager.h"


ASkill_SwiftPhantom::ASkill_SwiftPhantom()
{
	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("SwiftPhantom_Effect_Front", "SwiftPhantom_Effect_Front", 0, 3, 0.1f, false);
		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer));
	}
	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("SwiftPhantom_Effect_Back", "SwiftPhantom_Effect_Back", 0, 3, 0.1f, false);
		SpriteRenderers.insert(std::make_pair("Back", SpriteRenderer));
	}

	//	일반점프
	FrameState.CreateState(Skill_Frame::Start, [this](float _DeltaTime)
		{
			PlayerLogicValue& LogicValue = Player->GetBoolValue();
			if (LogicValue.IsGroundValue)
			{
				LogicValue.SetGroundTrue();
				SetActiveFalse();
				return;
			}

			if (UEngineInput::IsDown(Key))
			{
				LogicValue.PlusJumpCount();
				LogicValue.IsMoveAbleValue = false;
				ChangeState(Skill_Frame::Update);
				return;
			}
		},
		[this]()
		{
			SpriteRenderers["Front"]->SetActive(false);
			SpriteRenderers["Back"]->SetActive(false);
			PlayerLogicValue& LogicValue = Player->GetBoolValue();
			if (UEngineInput::IsPress(VK_DOWN)) {
				if (Player->GetDownableFloor()) {
					LogicValue.StartJump();
					LogicValue.StartFalling();
					Player->SetVelocityY(-200.0f);
					Player->ChangeAnimation(PAnimation_State::Jump);
				}

			}
			else {
				LogicValue.StartJump();
				Player->SetVelocityY(660.0f);
				
			}

		});

	//	더블점프
	FrameState.CreateState(Skill_Frame::Update, [this](float _DeltaTime)
		{
			PlayerLogicValue& LogicValue = Player->GetBoolValue();
			if (LogicValue.IsGroundValue)
			{
				LogicValue.SetGroundTrue();
				SetActiveFalse();
				return;
			}
			if (UEngineInput::IsDown(Key))
			{
				LogicValue.PlusJumpCount();
				ChangeState(Skill_Frame::End);
				return;

			}
		},
		[this]()
		{
			FVector PlayerDir = Player->GetBoolValue().PlayerDir;

			SpriteRenderers["Front"]->SetActive(true);
			SpriteRenderers["Back"]->SetActive(true);
			SpriteRenderers["Front"]->ChangeAnimation("SwiftPhantom_Effect_Front", true);
			SpriteRenderers["Back"]->ChangeAnimation("SwiftPhantom_Effect_Back", true);
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(0.0f, 0.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(0.0f, 0.0f, static_cast<float>(Z_ORDER::Skill_Back)));
			if (UEngineInput::IsPress(VK_UP)) {
				SpriteRenderers["Front"]->SetRotation(FVector(0.0f, 0.0f, -90.0f));
				SpriteRenderers["Back"]->SetRotation(FVector(0.0f, 0.0f, -90.0f));
				SpriteRenderers["Front"]->SetRelativeLocation(FVector(0.0f, 10.0f, static_cast<float>(Z_ORDER::Skill_Front)));
				SpriteRenderers["Back"]->SetRelativeLocation(FVector(0.0f, 10.0f, static_cast<float>(Z_ORDER::Skill_Back)));

				Player->AddVelocityY(800.0f);
			}
			else {
				SpriteRenderers["Front"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
				SpriteRenderers["Back"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
				SpriteRenderers["Front"]->SetRelativeLocation(FVector(30.0f, 30.0f, static_cast<float>(Z_ORDER::Skill_Front)));
				SpriteRenderers["Back"]->SetRelativeLocation(FVector(30.0f, 30.0f, static_cast<float>(Z_ORDER::Skill_Back)));

				Player->SetVelocityX(PlayerDir.X * 600.0f);
				Player->AddVelocityY(200.0f);
			}
		});
	//	트리플점프
	FrameState.CreateState(Skill_Frame::End, [this](float _DeltaTime)
		{
			PlayerLogicValue& LogicValue = Player->GetBoolValue();
			if (LogicValue.IsGroundValue)
			{
				LogicValue.SetGroundTrue();
				SetActiveFalse();
			}
		},
		[this]()
		{
			FVector PlayerDir = Player->GetBoolValue().PlayerDir;
			Player->SetVelocityX(PlayerDir.X * 800.0f);
			Player->AddVelocityY(150.0f);

			SpriteRenderers["Front"]->ChangeAnimation("SwiftPhantom_Effect_Front", true);
			SpriteRenderers["Back"]->ChangeAnimation("SwiftPhantom_Effect_Back", true);
			SpriteRenderers["Front"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
			SpriteRenderers["Back"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(30.0f, 30.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(30.0f, 30.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});
}

ASkill_SwiftPhantom::~ASkill_SwiftPhantom()
{

}

void ASkill_SwiftPhantom::BeginPlay()
{
	ASkill::BeginPlay();
}

void ASkill_SwiftPhantom::Tick(float _DeltaTime)
{
	ASkill::Tick(_DeltaTime);

}

void ASkill_SwiftPhantom::SetActiveTrue()
{
	ASkill::SetActiveTrue();
	Player = dynamic_cast<APlayer*>(Owner);
	Key = Player->GetPlayerFuncManager()->GetKey("SwiftPhantom");
	ChangeState(Skill_Frame::Start);
}




