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
	ImGui::Text("Player HP : %f", GetGameInstance<MyGameInstance>()->PlayerStatus.CurHp);
	ImGui::Text("Player MP : %f", GetGameInstance<MyGameInstance>()->PlayerStatus.CurMp);
	if (Dunkel != nullptr)
	{
		ImGui::Text("Dunkel Pos : %f %f %f", Dunkel->GetActorLocation().X, Dunkel->GetActorLocation().Y, Dunkel->GetActorLocation().Z);
	}

	if (ImGui::Button("LevelDubugMode"))
	{
		ULevel* Level = GetWorld();
		if (Level != nullptr)
		{
			Level->DebugSwitch();
		}
	}
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
			Dunkel->ChangeState(DunkelAnim_State::Spawn);
		}
	}

	if (ImGui::Button("StartStand"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Stand);
		}
	}

	if (ImGui::Button("StartDie"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Die);
		}
	}

	if (ImGui::Button("State_Spawn"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Spawn);
		}
	}

	if (ImGui::Button("StartForce"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Force);
		}
	}

	if (ImGui::Button("StartKnockback"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Knockback);
		}
	}

	if (ImGui::Button("StartMeteo"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Meteo);
		}
	}

	if (ImGui::Button("StartSlash_Start"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Slash_Start);
		}
	}

	if (ImGui::Button("StartSword"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Sword);
		}
	}

	if (ImGui::Button("StartUp"))
	{
		if (Dunkel != nullptr)
		{
			Dunkel->ChangeState(DunkelAnim_State::Up);
		}
	}


	if (ImGui::Button("CQ57"))
	{
		if (Dunkel != nullptr)
		{
			GetWorld()->SpawnActor<ACQ57>();
		}
	}

	if (ImGui::Button("Mogadin"))
	{
		if (Dunkel != nullptr)
		{
			GetWorld()->SpawnActor<AMogadin>();
		}
	}

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


	if (ImGui::Button("Jurai"))
	{
		if (Dunkel != nullptr)
		{
			GetWorld()->SpawnActor<AJurai>();
		}
	}

	
}
