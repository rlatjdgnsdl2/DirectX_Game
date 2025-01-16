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
				PlayerLogicValue& LogicValue = Player->GetBoolValue();
				Player->SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
				LogicValue.PlayerDir = FVector::LEFT;
				if (LogicValue.IsMoveAbleValue) {
					if (LogicValue.IsGroundValue) {

						float VelocityX = UEngineMath::Lerp(0.0f, 260.0f, UEngineMath::Clamp(UEngineInput::GetPressTime(VK_LEFT) * 4.0f, 0.0f, 1.0f));
						Player->SetVelocityX(-VelocityX);
					}

				}
				if (!(LogicValue.IsUsingSkillValue) && LogicValue.IsGroundValue) {
					Player->ChangeAnimation(PAnimation_State::Walk);
				}
			});
		NewFunc.AddUpEvent([this]()
			{
				if (Player->GetBoolValue().IsGroundValue) {
					Player->SetVelocityX(0.0f);
				}
			});
		SetFunc("VK_LEFT", NewFunc);
		SetFuncName(VK_LEFT, "VK_LEFT");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				PlayerLogicValue& LogicValue = Player->GetBoolValue();
				Player->SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
				LogicValue.PlayerDir = FVector::RIGHT;
				if (LogicValue.IsMoveAbleValue) {
					if (LogicValue.IsGroundValue) {
						float VelocityX = UEngineMath::Lerp(0.0f, 260.0f, UEngineMath::Clamp(UEngineInput::GetPressTime(VK_RIGHT) * 4.0f, 0.0f, 1.0f));
						Player->SetVelocityX(VelocityX);
					}
				}
				if (!(LogicValue.IsUsingSkillValue) && LogicValue.IsGroundValue) {
					Player->ChangeAnimation(PAnimation_State::Walk);
				}
			});
		NewFunc.AddUpEvent([this]()
			{
				if (Player->GetBoolValue().IsGroundValue) {
					Player->SetVelocityX(0.0f);
				}
			});
		SetFunc("VK_RIGHT", NewFunc);
		SetFuncName(VK_RIGHT, "VK_RIGHT");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				PlayerLogicValue& LogicValue = Player->GetBoolValue();
				if (!(LogicValue.IsUsingSkillValue) && LogicValue.IsGroundValue) {
					Player->ChangeAnimation(PAnimation_State::Prone);

					LogicValue.IsMoveAbleValue = false;
					LogicValue.IsProneValue = true;
				}
			});
		NewFunc.AddUpEvent([this]()
			{
				PlayerLogicValue& LogicValue = Player->GetBoolValue();

				LogicValue.IsMoveAbleValue = true;
				LogicValue.IsProneValue = false;
			});
		SetFunc("VK_DOWN", NewFunc);
		SetFuncName(VK_DOWN, "VK_DOWN");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				PlayerLogicValue& LogicValue = Player->GetBoolValue();

				LogicValue.IsJumpAbleValue;
				if (LogicValue.IsJumpAbleValue) {
					if (nullptr != Player->GetSkill("SwiftPhantom")) {
						if (!Player->GetSkill("SwiftPhantom")->IsActive()) {
							Player->GetSkill("SwiftPhantom")->SetActiveTrue();
						}
					}
				}
				if (!LogicValue.IsUsingSkillValue) {
					if (LogicValue.IsJumpingValue || LogicValue.IsFallingValue)
					{
						Player->ChangeAnimation(PAnimation_State::Jump);
					}
				}
			});
		SetFunc("SwiftPhantom", NewFunc);
		SetFuncName('C', "SwiftPhantom");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				PlayerLogicValue& LogicValue = Player->GetBoolValue();
				if (nullptr != Player->GetSkill("UltimateDrive")) {
					if (!Player->GetSkill("UltimateDrive")->IsActive()) {
						Player->GetSkill("UltimateDrive")->SetActiveTrue();
					}
				}
				LogicValue.IsUsingSkillValue = true;
				LogicValue.IsMoveAbleValue = true;
				LogicValue.IsJumpAbleValue = false;
				Player->ChangeAnimation(PAnimation_State::Ultimate_Drive);
			});
		SetFunc("UltimateDrive", NewFunc);
		SetFuncName('Z', "UltimateDrive");
	}

}

UPlayerFuncManager::~UPlayerFuncManager()
{

}
