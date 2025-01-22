#include "PreCompile.h"
#include "EngineGUIWindow.h"

UEngineGUIWindow::UEngineGUIWindow()
{
}

UEngineGUIWindow::~UEngineGUIWindow()
{
}


UGameInstance* UEngineGUIWindow::GetGameInstance()
{
	return GEngine->GetGameInstance();
}

