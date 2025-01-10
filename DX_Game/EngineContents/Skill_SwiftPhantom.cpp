#include "PreCompile.h"
#include "Skill_SwiftPhantom.h"

#include "Player.h"
#include "PlayerFuncManager.h"


ASkill_SwiftPhantom::ASkill_SwiftPhantom()
{
	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("SwiftPhantom_Effect_Front", "SwiftPhantom_Effect_Front", 0, 3,0.1f,false);
		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer));
	}
	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("SwiftPhantom_Effect_Back", "SwiftPhantom_Effect_Back", 0, 3,0.1f,false);
		SpriteRenderers.insert(std::make_pair("Back", SpriteRenderer));
	}

	//	�Ϲ�����
	FrameState.CreateState(Skill_Frame::Start, [this](float _DeltaTime)
		{
			PlayerLogicValue& LogicValue = Player->GetBoolValue();
			if (LogicValue.IsGroundValue) 
			{
				LogicValue.SetGroundTrue();
				SetActiveFalse();
			}

			if (UEngineInput::IsDown(Key))
			{
				LogicValue.PlusJumpCount();
				ChangeState(Skill_Frame::Update);
			}
		},
		[this]()
		{
			PlayerLogicValue& LogicValue = Player->GetBoolValue();
			LogicValue.StartJump();
			Player->SetJumpPower(0.0f, 300.0f);
			SpriteRenderers["Front"]->SetActive(false);
			SpriteRenderers["Back"]->SetActive(false);
		});

	//	��������
	FrameState.CreateState(Skill_Frame::Update, [this](float _DeltaTime)
		{
			PlayerLogicValue& LogicValue = Player->GetBoolValue();
			if (LogicValue.IsGroundValue)
			{
				LogicValue.SetGroundTrue();
				SetActiveFalse();
			}
			if (UEngineInput::IsDown(Key))
			{
				LogicValue.PlusJumpCount();
				ChangeState(Skill_Frame::End);

			}
		},
		[this]()
		{
			FVector PlayerDir = Player->GetBoolValue().GetPlayerDir();
			Player->SetJumpPower(PlayerDir.X * 300.0f, 100.0f);
			SpriteRenderers["Front"]->SetActive(true);
			SpriteRenderers["Back"]->SetActive(true);
			SpriteRenderers["Front"]->ChangeAnimation("SwiftPhantom_Effect_Front",true);
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(70.0f, 0.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("SwiftPhantom_Effect_Back", true);
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(50.0f, -20.0f, static_cast<float>(Z_ORDER::Skill_Back)));

		});
	//	Ʈ��������
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
			FVector PlayerDir = Player->GetBoolValue().GetPlayerDir();
			Player->SetJumpPower(PlayerDir.X * 300.0f, 100.0f);
			SpriteRenderers["Front"]->ChangeAnimation("SwiftPhantom_Effect_Front",true);
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(70.0f, 0.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("SwiftPhantom_Effect_Back", true);
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(50.0f, -20.0f, static_cast<float>(Z_ORDER::Skill_Back)));
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
	Update(_DeltaTime);
}

void ASkill_SwiftPhantom::SetActiveTrue()
{
	ASkill::SetActiveTrue();
	Player = dynamic_cast<APlayer*>(Owner);
	Key = Player->GetPlayerFuncManager()->GetKey("SwiftPhantom");
	ChangeState(Skill_Frame::Start);
}




