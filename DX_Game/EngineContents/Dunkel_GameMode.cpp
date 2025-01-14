#include "PreCompile.h"
#include "Dunkel_GameMode.h"
#include "Dunkel_Map.h"


ADunkel_GameMode::ADunkel_GameMode() 
{

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\MoonBridge\\DunkelMap");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
		Dir.Append("DunkelMapBackGround");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("DunkelMapObject_Sphere");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("DunkelMapObject_Stone");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();
	}
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\Monster\\Dunkel");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
		Dir.Append("Dunkel_Spawn");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Stand");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());

	}


	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("FootHold");
	GetWorld()->CreateCollisionProfile("UI");
	GetWorld()->CreateCollisionProfile("EndArea");
	GetWorld()->CreateCollisionProfile("PlayerSkill");

	Map = GetWorld()->SpawnActor<ADunkel_Map>();
	Dunkel = GetWorld()->SpawnActor<ADunkel>();


}

ADunkel_GameMode::~ADunkel_GameMode() 
{
	Map = nullptr;
	Dunkel = nullptr;

}
