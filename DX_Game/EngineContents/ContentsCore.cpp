#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineCore.h>

#include "Carcion_Ishfira.h"
#include "Player.h"
#include "EngineCore/EngineTexture.h"
#include "EngineCore/EngineSprite.h"



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

	
	LoadPlayerResources();

	UEngineCore::CreateLevel<ACarcion_Ishfira, APlayer>("Carcion_Ishfira");
	UEngineCore::OpenLevel("Carcion_Ishfira");
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}