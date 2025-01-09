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
				if (Player->IsMoveAble()) {
					Player->AddActorLocation(FVector(-100.0f * Player->GetDeltaTime(), 0.0f, 0.0f));
				}
				if (!(Player->IsSkill()) && Player->IsGround()) {
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
				if (Player->IsMoveAble()) {
					Player->AddActorLocation(FVector(100.0f * Player->GetDeltaTime(), 0.0f, 0.0f));
				}
				if (!(Player->IsSkill()) && Player->IsGround()) {
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
				if (!(Player->IsSkill()) && Player->IsGround()) {
					Player->ChangeAnimation(PAnimation_State::Prone);
				}
			});
		SetFunc("VK_DOWN", NewFunc);
		SetFuncName(VK_DOWN, "VK_DOWN");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddEvent([this]()
			{
				if (Player->IsJumpAble()) {
					Player->AddActorLocation(FVector::UP * 100.0f * Player->GetDeltaTime());
				}
				if (!Player->IsSkill()) {
					if (Player->IsJump() || Player->IsFalling())
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
				if (nullptr == Player->GetSkill("Ultimate_Drive")) {
					std::shared_ptr<ASkill_UltimateDrive> Skill = Player->GetWorld()->SpawnActor<ASkill_UltimateDrive>();
					Skill->SetOwner(Player);
					Player->SetSkillStart("Ultimate_Drive", Skill);
					Player->SetSkill(true);
					Player->SetMoveAble(true);
					Player->SetJumpAble(false);
				}
				Player->ChangeAnimation(PAnimation_State::Ultimate_Drive);
			});
		SetFunc("Ultimate_Drive", NewFunc);
		SetFuncName('Z', "Ultimate_Drive");
	}

}

UPlayerFuncManager::~UPlayerFuncManager()
{

}
