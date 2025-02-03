#include "PreCompile.h"
#include "Skill_SwiftPhantom.h"

#include "Player.h"
#include "PlayerFuncManager.h"
#include "PhysicsComponent.h"


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
	FSM.CreateState(ESkill_Frame::First, std::bind(&ASkill_SwiftPhantom::UpdateJump, this, std::placeholders::_1), std::bind(&ASkill_SwiftPhantom::StartJump, this));
	FSM.CreateState(ESkill_Frame::Second, std::bind(&ASkill_SwiftPhantom::UpdateDoubleJump, this, std::placeholders::_1), std::bind(&ASkill_SwiftPhantom::StartDoubleJump, this));
	FSM.CreateState(ESkill_Frame::Third, std::bind(&ASkill_SwiftPhantom::UpdateTripleJump, this, std::placeholders::_1), std::bind(&ASkill_SwiftPhantom::StartTripleJump, this));
}

ASkill_SwiftPhantom::~ASkill_SwiftPhantom()
{

}


void ASkill_SwiftPhantom::SetActiveTrue()
{
	ASkill::SetActiveTrue();
	Key = Player->GetPlayerFuncManager()->GetKey(EPlayer_Function::Swift_Phantom);
	ChangeState(ESkill_Frame::First);
}

void ASkill_SwiftPhantom::StartJump()
{
	SpriteRenderers["Front"]->SetActive(false);
	SpriteRenderers["Back"]->SetActive(false);
}

void ASkill_SwiftPhantom::UpdateJump(float _DeltaTime)
{
	if (Player->GetPysicComponent()->IsGround())
	{
		SetActiveFalse();
		return;
	}

	if (UEngineInput::IsDown(Key))
	{
		ChangeState(ESkill_Frame::Second);
		return;
	}
}

void ASkill_SwiftPhantom::StartDoubleJump()
{
	SpriteRenderers["Front"]->SetActive(true);
	SpriteRenderers["Back"]->SetActive(true);
	SpriteRenderers["Front"]->ChangeAnimation("SwiftPhantom_Effect_Front", true);
	SpriteRenderers["Back"]->ChangeAnimation("SwiftPhantom_Effect_Back", true);
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(0.0f, 0.0f, UContentsConst::P_EFFECT_FRONT_ZPOS));
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(0.0f, 0.0f, UContentsConst::P_EFFECT_BACK_ZPOS));
	if (UEngineInput::IsPress(VK_UP)) {
		SpriteRenderers["Front"]->SetRotation(FVector(0.0f, 0.0f, -90.0f));
		SpriteRenderers["Back"]->SetRotation(FVector(0.0f, 0.0f, -90.0f));
		SpriteRenderers["Front"]->SetRelativeLocation(FVector(0.0f, 10.0f, UContentsConst::P_EFFECT_FRONT_ZPOS));
		SpriteRenderers["Back"]->SetRelativeLocation(FVector(0.0f, 10.0f, UContentsConst::P_EFFECT_BACK_ZPOS));
		Player->GetPysicComponent()->AddVelocityY(800.0f);
	}
	else {
		SpriteRenderers["Front"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
		SpriteRenderers["Back"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
		SpriteRenderers["Front"]->SetRelativeLocation(FVector(30.0f, 30.0f, UContentsConst::P_EFFECT_FRONT_ZPOS));
		SpriteRenderers["Back"]->SetRelativeLocation(FVector(30.0f, 30.0f, UContentsConst::P_EFFECT_BACK_ZPOS));
		Player->GetPysicComponent()->SetVelocityX(-Player->GetActorTransform().Scale.X * 600.0f);
		Player->GetPysicComponent()->AddVelocityY(250.0f);
	}
}

void ASkill_SwiftPhantom::UpdateDoubleJump(float _DeltaTime)
{
	if (Player->GetPysicComponent()->IsGround())
	{
		SetActiveFalse();
		return;
	}
	
	if (UEngineInput::IsDown(Key))
	{
		ChangeState(ESkill_Frame::Third);
		return;

	}

	if (SpriteRenderers["Front"]->IsCurAnimationEnd())
	{
		SpriteRenderers["Front"]->SetActive(false);
		SpriteRenderers["Back"]->SetActive(false);
	}
}

void ASkill_SwiftPhantom::StartTripleJump()
{
	Player->GetPysicComponent()->SetVelocityX(-Player->GetActorTransform().Scale.X * 800.0f);
	Player->GetPysicComponent()->AddVelocityY(250.0f);

	SpriteRenderers["Front"]->SetActive(true);
	SpriteRenderers["Back"]->SetActive(true);
	SpriteRenderers["Front"]->ChangeAnimation("SwiftPhantom_Effect_Front", true);
	SpriteRenderers["Back"]->ChangeAnimation("SwiftPhantom_Effect_Back", true);
	SpriteRenderers["Front"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
	SpriteRenderers["Back"]->SetRotation(FVector(0.0f, 0.0f, 0.0f));
	SpriteRenderers["Front"]->SetRelativeLocation(FVector(30.0f, 30.0f, UContentsConst::P_EFFECT_FRONT_ZPOS));
	SpriteRenderers["Back"]->SetRelativeLocation(FVector(30.0f, 30.0f, UContentsConst::P_EFFECT_BACK_ZPOS));
}

void ASkill_SwiftPhantom::UpdateTripleJump(float _DeltaTime)
{
	if (Player->GetPysicComponent()->IsGround())
	{
		SetActiveFalse();
		return;
	}
	if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsDown(VK_LEFT)) {
		Player->SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	else if (UEngineInput::IsPress(VK_RIGHT) || UEngineInput::IsDown(VK_RIGHT)) {
		Player->SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
	}
	if (SpriteRenderers["Front"]->IsCurAnimationEnd())
	{
		SpriteRenderers["Front"]->SetActive(false);
		SpriteRenderers["Back"]->SetActive(false);
	}
}




