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
		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer.get()));
	}
	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("SwiftPhantom_Effect_Back", "SwiftPhantom_Effect_Back", 0, 3, 0.1f, false);
		SpriteRenderers.insert(std::make_pair("Back", SpriteRenderer.get()));
	}

	//	일반점프
	FrameState.CreateState(Skill_Frame::Start, [this](float _DeltaTime)
		{
			FPlayerLogic& LogicValue = Player->GetPlayerLogic();
			if (LogicValue.bIsGround)
			{
				LogicValue.SetGroundTrue();
				SetActiveFalse();
				return;
			}

			if (UEngineInput::IsDown(Key))
			{
				LogicValue.PlusJumpCount();
				LogicValue.bIsMoveAble = false;
				ChangeState(Skill_Frame::Update);
				return;
			}
		},
		[this]()
		{
			
			SpriteRenderers["Front"]->SetActive(false);
			SpriteRenderers["Back"]->SetActive(false);
			FPlayerLogic& LogicValue = Player->GetPlayerLogic();
			if (UEngineInput::IsPress(VK_DOWN)) {
				if (LogicValue.bIsDownableFloor) {
					LogicValue.StartJump();
					LogicValue.StartFalling();
					Player->GetPlayerLogic().SetVelocityY(-200.0f);
					Player->ChangeAnimation("Jump");
				}

			}
			else {
				LogicValue.StartJump();
				Player->GetPlayerLogic().SetVelocityY(660.0f);
				
			}

		});

	//	더블점프
	FrameState.CreateState(Skill_Frame::Update, [this](float _DeltaTime)
		{
			FPlayerLogic& LogicValue = Player->GetPlayerLogic();
			if (LogicValue.bIsGround)
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

			if (SpriteRenderers["Front"]->IsCurAnimationEnd())
			{
				SpriteRenderers["Front"]->SetActive(false);
				SpriteRenderers["Back"]->SetActive(false);
			}

		},
		[this]()
		{
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
				Player->GetPlayerLogic().AddVelocityY(800.0f);
			}
			else {
				SpriteRenderers["Front"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
				SpriteRenderers["Back"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
				SpriteRenderers["Front"]->SetRelativeLocation(FVector(30.0f, 30.0f, static_cast<float>(Z_ORDER::Skill_Front)));
				SpriteRenderers["Back"]->SetRelativeLocation(FVector(30.0f, 30.0f, static_cast<float>(Z_ORDER::Skill_Back)));

				Player->GetPlayerLogic().SetVelocityX(-Player->GetActorTransform().Scale.X * 600.0f);
				Player->GetPlayerLogic().AddVelocityY(250.0f);
			}
		});
	//	트리플점프
	FrameState.CreateState(Skill_Frame::End, [this](float _DeltaTime)
		{
			FPlayerLogic& LogicValue = Player->GetPlayerLogic();
			if (LogicValue.bIsGround)
			{
				LogicValue.SetGroundTrue();
				SetActiveFalse();
			}
			if (SpriteRenderers["Front"]->IsCurAnimationEnd())
			{
				SpriteRenderers["Front"]->SetActive(false);
				SpriteRenderers["Back"]->SetActive(false);
			}
		},
		[this]()
		{
			Player->GetPlayerLogic().SetVelocityX(-Player->GetActorTransform().Scale.X * 800.0f);
			Player->GetPlayerLogic().AddVelocityY(250.0f);

			SpriteRenderers["Front"]->SetActive(true);
			SpriteRenderers["Back"]->SetActive(true);
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




