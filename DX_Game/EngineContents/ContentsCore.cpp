#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineCore.h>

#include "TempGameMode.h"
#include "TempPawn.h"
#include "EngineCore/EngineTexture.h"
#include "EngineCore/EngineSprite.h"



CreateContentsCoreDefine(UContentsCore);
//STDAPI_(__declspec(dllexport) INT_PTR) CreateContentsCore(std::shared_ptr<IContentsCore>& _Test)
//{ 
//	_Test = std::make_shared<UContentsCore>();
//	if (nullptr == _Test) 
//	{ 
//		MSGASSERT("������ ��� ������ �����߽��ϴ�."); 
//	} 
//	return 0; 
//}

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
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	UEngineSprite::CreateSpriteToMeta("Player.png", ".sdata");
	UEngineCore::CreateLevel<ATempGameMode, ATempPawn>("TempLevel");
	UEngineCore::OpenLevel("TempLevel");
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}