#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineCore.h>

#include "MoonBridge_WhiteSpear.h"
#include "Player.h"

#include "Dunkel_GameMode.h"
#include "Dunkel_HUD.h"
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>
#include "ContentsEditorGUI.h"

#include "MyGameInstance.h"




CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	GEngine->CreateGameInstance<MyGameInstance>();
	




	LoadResources();

	UEngineCore::CreateLevel<AMoonBridge_WhiteSpear, APlayer,AHUD>("MoonBridge_WhiteSpear");
	UEngineCore::CreateLevel<ADunkel_GameMode, APlayer, ADunkel_HUD>("Dunkel");
	UEngineCore::OpenLevel("Dunkel");
	

	UEngineGUI::AllWindowOff();
	UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	Window->SetActive(true);
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}