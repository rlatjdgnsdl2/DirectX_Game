#include "PreCompile.h"
#include "TempGameMode.h"

#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>


#include "TempActor.h"



class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		ImGui::Button("WindowButton");
		ImGui::SameLine(); // ÇÑ°£ ¶ç±â
		ImGui::Text("test");

	}
};

ATempGameMode::ATempGameMode() 
{
	TempActor = GetWorld()->SpawnActor<ATempActor>();
	TempActor->SetActorLocation({ 300.0f, 0.0f, 0.0f });
	TempActor->GetRenderer()->SetSpriteData(4);

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });

	UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
}

ATempGameMode::~ATempGameMode() 
{

}

void ATempGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
