#include "PreCompile.h"
#include "Carcion_Ishfira.h"
#include "Carcion_Ishfira_map.h"
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>


ACarcion_Ishfira::ACarcion_Ishfira() 
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image//Carcion");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}

		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("Resources"))
			{
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
				return;
			}
			Dir.Append("Image//Carcion//Ishfira");
			UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		}
		
	}

	Carcion_Ishfira_Map = GetWorld()->SpawnActor<ACarcion_Ishfira_Map>();
}

ACarcion_Ishfira::~ACarcion_Ishfira() 
{
	Carcion_Ishfira_Map = nullptr;
}