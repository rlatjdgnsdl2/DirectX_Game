#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineCore.h>

#include "MoonBridge_WhiteSpear.h"
#include "Player.h"

#include "Dunkel_GameMode.h"





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

	
	LoadResources();

	UEngineCore::CreateLevel<AMoonBridge_WhiteSpear, APlayer,AHUD>("MoonBridge_WhiteSpear");
	UEngineCore::CreateLevel<ADunkel_GameMode, APlayer, AHUD>("Dunkel");
	//UEngineCore::OpenLevel("MoonBridge_WhiteSpear");
	UEngineCore::OpenLevel("Dunkel");
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}