#include "PreCompile.h"
#include "Dunkel_GUI.h"
#include "Player.h"
#include "Dunkel_Boss.h"
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineCore.h>
#include "MyGameInstance.h"

#include "CQ57.h"
#include "Freyd.h"
#include "Jurai.h"
#include "Khaliain.h"
#include "Mogadin.h"

#include "PlayerFuncManager.h"


UDunkel_GUI::UDunkel_GUI()
{

}

UDunkel_GUI::~UDunkel_GUI()
{

}

void UDunkel_GUI::BeginPlay()
{
	UEngineGUIWindow::BeginPlay();
}

void UDunkel_GUI::OnGUI()
{
	if (Player == nullptr)
	{
		Player = dynamic_cast<APlayer*>(GetWorld()->GetMainPawn());
	}

	ImGui::Text("Player Pos : %f %f %f", Player->GetActorLocation().X, Player->GetActorLocation().Y, Player->GetActorLocation().Z);
	ImGui::Text("Player State : %d ", static_cast<int>(Player->GetFSM().GetCurStateValue<EPlayer_State>()));
	ImGui::Text("Player HP : %f", GetGameInstance<MyGameInstance>()->PlayerStatus.CurHp);
	ImGui::Text("Player MP : %f", GetGameInstance<MyGameInstance>()->PlayerStatus.CurMp);

	if (Dunkel != nullptr)
	{
		ImGui::Text("Dunkel Pos : %f %f %f", Dunkel->GetActorLocation().X, Dunkel->GetActorLocation().Y, Dunkel->GetActorLocation().Z);
	}
	ImGui::Text("CollisionTest");
	if (ImGui::Button("LevelDubugMode"))
	{
		ULevel* Level = GetWorld();
		if (Level != nullptr)
		{
			Level->DebugSwitch();
		}
	}
	ImGui::Text("PatternTest");
	if (ImGui::Button("DunkelDubugMode"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->DebugSwitch();
		}
	}

	if (ImGui::Button("StartSpawn"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Spawn);
		}
	}

	ImGui::SameLine();

	if (ImGui::Button("StartStand"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Stand);
		}
	}
	ImGui::SameLine();

	if (ImGui::Button("StartDie"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Die);
		}
	}
	ImGui::SameLine();

	if (ImGui::Button("State_Spawn"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Spawn);
		}
	}

	if (ImGui::Button("StartForce"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Force);
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("StartKnockback"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Knockback);
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("StartMeteo"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Meteo);
		}
	}

	if (ImGui::Button("StartSlash_Start"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Slash_Start);
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("StartSword"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Sword);
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("StartUp"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(EDunkelAnim_State::Up);
		}
	}


	if (ImGui::Button("CQ57"))
	{
		if (Dunkel != nullptr)
		{
			GetWorld()->SpawnActor<ACQ57>();
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Mogadin"))
	{
		if (Dunkel != nullptr)
		{
			GetWorld()->SpawnActor<AMogadin>();
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Freyd"))
	{
		if (Dunkel != nullptr)
		{
			GetWorld()->SpawnActor<AFreyd>();
		}
	}

	if (ImGui::Button("Khaliain"))
	{
		if (Dunkel != nullptr)
		{
			GetWorld()->SpawnActor<AKhaliain>();
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Jurai"))
	{
		if (Dunkel != nullptr)
		{
			GetWorld()->SpawnActor<AJurai>();
		}
	}
	ImGui::Text("Move - Dir Key");

	ImGui::Text("6thSkill - %c", static_cast<char>(Player->GetPlayerFuncManager()->GetKey(EPlayer_Function::Defying_Fate)));
	ImGui::Text("Skill - Z KeyPress");
	ImGui::Text("Skill - W KeyPress");
	ImGui::Text("Jump - C Key");






}
