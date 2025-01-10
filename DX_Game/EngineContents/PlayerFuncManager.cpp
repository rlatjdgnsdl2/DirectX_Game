#include "PreCompile.h"
#include "PlayerFuncManager.h"
#include "Player.h"
#include "Skill_UltimateDrive.h"



UPlayerFuncManager::UPlayerFuncManager()
{
	Player = dynamic_cast<APlayer*>(GetActor());
	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				Player->SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
				if (Player->GetBoolValue().IsMoveAbleValue){
					Player->AddActorLocation(FVector(-100.0f * Player->GetDeltaTime(), 0.0f, 0.0f));
				}
				if (!(Player->GetBoolValue().IsSkillValue) && Player->GetBoolValue().IsGroundValue) {
					Player->ChangeAnimation(PAnimation_State::Walk);
				}
			});
		SetFunc("VK_LEFT", NewFunc);
		SetFuncName(VK_LEFT, "VK_LEFT");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				Player->SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
				if (Player->GetBoolValue().IsMoveAbleValue) {
					Player->AddActorLocation(FVector(100.0f * Player->GetDeltaTime(), 0.0f, 0.0f));
				}
				if (!(Player->GetBoolValue().IsSkillValue) && Player->GetBoolValue().IsGroundValue) {
					Player->ChangeAnimation(PAnimation_State::Walk);
				}
			});
		SetFunc("VK_RIGHT", NewFunc);
		SetFuncName(VK_RIGHT, "VK_RIGHT");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				if (!(Player->GetBoolValue().IsSkillValue) && Player->GetBoolValue().IsGroundValue) {
					Player->ChangeAnimation(PAnimation_State::Prone);
					Player->GetBoolValue().SetMoveAble(false);
					Player->GetBoolValue().SetProne(true);
				}
			});
		NewFunc.AddUpEvent([this]()
			{
				Player->GetBoolValue().SetMoveAble(true);
				Player->GetBoolValue().SetProne(false);
			});
		SetFunc("VK_DOWN", NewFunc);
		SetFuncName(VK_DOWN, "VK_DOWN");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				if (Player->GetBoolValue().IsJumpAbleValue) {
					Player->GetBoolValue().SetJump(true);
					Player->GetBoolValue().SetJumpAble(true);
					Player->GetBoolValue().SetGround(false);
				}
				if (!Player->GetBoolValue().IsSkillValue) {
					if (Player->GetBoolValue().IsJumpingValue || Player->GetBoolValue().IsFallingValue)
					{
						Player->ChangeAnimation(PAnimation_State::Jump);
					}
				}
			});
		SetFunc("Jump", NewFunc);
		SetFuncName('C', "Jump");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				if (nullptr != Player->GetSkill("UltimateDrive")) {
					if (!Player->GetSkill("UltimateDrive")->IsActive()) {
						Player->GetSkill("UltimateDrive")->SetActiveTrue();
					}
				}
				Player->GetBoolValue().SetSkill(true);
				Player->GetBoolValue().SetMoveAble(true);
				Player->GetBoolValue().SetJumpAble(false);
				Player->ChangeAnimation(PAnimation_State::Ultimate_Drive);
			});
		SetFunc("UltimateDrive", NewFunc);
		SetFuncName('Z', "UltimateDrive");
	}

}

UPlayerFuncManager::~UPlayerFuncManager()
{

}
