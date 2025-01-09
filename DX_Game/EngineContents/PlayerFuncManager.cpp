#include "PreCompile.h"
#include "PlayerFuncManager.h"
#include "Player.h"
#include "Skill_UltimateDrive.h"



UPlayerFuncManager::UPlayerFuncManager()
{
	Player = dynamic_cast<APlayer*>(GetActor());
	{
		UPlayerFunc NewFunc;
		NewFunc.AddPressEvent([this]()
			{
				Player->SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
				Player->AddActorLocation(FVector(-100.0f*Player->GetDeltaTime(), 0.0f, 0.0f));
				PAnimation_State CurAnimState = Player->GetPlayerAnimation().GetFSM().GetCurStateValue<PAnimation_State>();
				bool IsChange = Player->CheckAnimNode(CurAnimState, PAnimation_State::Walk);
				if (IsChange)
				{
					Player->ChangeAnimation(PAnimation_State::Walk);
				}
				Player->ChangeState(Player_State::Walk);
			});

		SetFunc("VK_LEFT", NewFunc);
		SetFuncName(VK_LEFT, "VK_LEFT");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddPressEvent([this]()
			{
				Player->SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
				Player->AddActorLocation(FVector(100.0f * Player->GetDeltaTime(), 0.0f, 0.0f));
				PAnimation_State CurAnimState = Player->GetPlayerAnimation().GetFSM().GetCurStateValue<PAnimation_State>();
				bool IsChange = Player->CheckAnimNode(CurAnimState, PAnimation_State::Walk);
				if (IsChange)
				{
					Player->ChangeAnimation(PAnimation_State::Walk);
				}
				Player->ChangeState(Player_State::Walk);
			});
		SetFunc("VK_RIGHT", NewFunc);
		SetFuncName(VK_RIGHT, "VK_RIGHT");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddPressEvent([this]()
			{
				PAnimation_State CurAnimState = Player->GetPlayerAnimation().GetFSM().GetCurStateValue<PAnimation_State>();
				bool IsChange = Player->CheckAnimNode(CurAnimState, PAnimation_State::Walk);
				if (IsChange)
				{
					Player->ChangeAnimation(PAnimation_State::Prone);
				}
				Player->ChangeState(Player_State::Prone);
			});
		SetFunc("VK_DOWN", NewFunc);
		SetFuncName(VK_DOWN, "VK_DOWN");
	}



	{
		UPlayerFunc NewFunc;
		NewFunc.AddPressEvent([this]()
			{
				Player->AddActorLocation(FVector::UP*100.0f*Player->GetDeltaTime());
				PAnimation_State CurAnimState = Player->GetPlayerAnimation().GetFSM().GetCurStateValue<PAnimation_State>();
				bool IsChange = Player->CheckAnimNode(CurAnimState, PAnimation_State::Jump);
				if (IsChange)
				{
					Player->ChangeAnimation(PAnimation_State::Jump);
				}
				Player->ChangeState(Player_State::Jump);
			});
		SetFunc("Jump", NewFunc);
		SetFuncName('C', "Jump");
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddPressEvent([this]()
			{
				if (nullptr == Player->GetSkill("Ultimate_Drive")) {
					std::shared_ptr<ASkill_UltimateDrive> Skill = Player->GetWorld()->SpawnActor<ASkill_UltimateDrive>();
					Skill->SetOwner(Player);
					Player->SetSkillStart("Ultimate_Drive", Skill);
				}
				PAnimation_State CurAnimState = Player->GetPlayerAnimation().GetFSM().GetCurStateValue<PAnimation_State>();
				bool IsChange = Player->CheckAnimNode(CurAnimState, PAnimation_State::Jump);
				if (IsChange)
				{
					Player->ChangeAnimation(PAnimation_State::Ultimate_Drive);
				}
				Player->ChangeState(Player_State::Ultimate_Drive);
			});
		SetFunc("Ultimate_Drive", NewFunc);
		SetFuncName('Z', "Ultimate_Drive");
	}





}

UPlayerFuncManager::~UPlayerFuncManager()
{

}
