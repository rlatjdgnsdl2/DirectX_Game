#include "PreCompile.h"
#include "ContentsCore.h"

void UContentsCore::LoadResources() 
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\Player");
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
		Dir.Append("Image\\Player\\Player_Skill\\UltimateDrive_KeyDown_Effect_Front");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("UltimateDrive_KeyDown_Effect_Back");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("UltimateDrive_Start_Effect_Front");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("UltimateDrive_Start_Effect_Back");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("UltimateDrive_End_Effect_Front");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("UltimateDrive_End_Effect_Back");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("SwiftPhantom_Effect_Back");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("SwiftPhantom_Effect_Front");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

	}

	UEngineSprite::CreateSpriteToMeta("Player_Stand.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Player_Walk.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Player_Jump.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Player_Prone.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Player_UltimateDrive_KeyDown.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Player_UltimateDrive_StartEnd.png", ".sdata");


	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\UI");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}



}