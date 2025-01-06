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

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image//Player");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image//Player//Ultimate_Drive");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}






	UEngineSprite::CreateSpriteToMeta("Player_Stand.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Player_Walk.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Player_Jump.png", ".sdata");

	UEngineCore::CreateLevel<ACarcion_Ishfira, APlayer>("Carcion_Ishfira");
	UEngineCore::OpenLevel("Carcion_Ishfira");
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}