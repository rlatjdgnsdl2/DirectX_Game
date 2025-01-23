#include "PreCompile.h"
#include "Dunkel_GUI.h"
#include "Player.h"
#include "Dunkel_Boss.h"
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineCore.h>
#include "MyGameInstance.h"

UDunkel_GUI::UDunkel_GUI()
{

}

UDunkel_GUI::~UDunkel_GUI()
{

}

void UDunkel_GUI::BeginPlay()
{


}

void UDunkel_GUI::OnGUI()
{
	Player = dynamic_cast<APlayer*>(GetWorld()->GetMainPawn());
	ImGui::Text("Player Pos : %f %f %f", Player->GetActorLocation().X, Player->GetActorLocation().Y, Player->GetActorLocation().Z);
	ImGui::Text("Dunkel Pos : %f %f %f", Dunkel->GetActorLocation().X, Dunkel->GetActorLocation().Y, Dunkel->GetActorLocation().Z);
	ImGui::Text("Player HP : %f",GetGameInstance<MyGameInstance>()->PlayerStatus.Hp);
	ImGui::Text("Player MP : %f", GetGameInstance<MyGameInstance>()->PlayerStatus.Mp);
	
	if (ImGui::Button("DubugMode"))
	{
		GetWorld()->DebugSwitch();
	}
}
