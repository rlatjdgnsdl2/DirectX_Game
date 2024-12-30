#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineCore.h>

#include "Carcion_Ishfira.h"
#include "Player.h"
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
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image//Player//Player_Walk");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image//Player//Player_Idle");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	UEngineCore::CreateLevel<ACarcion_Ishfira, APlayer>("Carcion_Ishfira");
	UEngineCore::OpenLevel("Carcion_Ishfira");
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}