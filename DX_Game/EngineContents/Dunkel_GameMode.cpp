#include "PreCompile.h"
#include "Dunkel_GameMode.h"
#include "Dunkel_Map.h"
#include "Dunkel_Boss.h"
#include "FallenWarrior.h"


ADunkel_GameMode::ADunkel_GameMode()
{

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\Boss\\Boss_Dunkel");
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
		Dir.Append("Image\\Boss\\Boss_Dunkel");
		Dir.Append("DunkelMapBackGround");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("DunkelMapObject_Sphere");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("DunkelMapObject_Stone");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel\\Dunkel_KnockBack");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Spawn");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Stand");
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
		Dir.Append("Image\\Boss\\Boss_Dunkel\\FallenWarrior");

		Dir.Append("FallenWarrior_Attack");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("FallenWarrior_Die");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("FallenWarrior_Move");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("FallenWarrior_Spawn");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("FallenWarrior_Stand");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();
	}


	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->CreateCollisionProfile("PlayerSkill");
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Boss");
	GetWorld()->CreateCollisionProfile("BossAttack");
	GetWorld()->CreateCollisionProfile("UI");
	GetWorld()->CreateCollisionProfile("EndArea");



	Map = GetWorld()->SpawnActor<ADunkel_Map>();
	Dunkel = GetWorld()->SpawnActor<ADunkel_Boss>();

	GetWorld()->GetMainCamera()->GetCameraComponent()->SetZSort(0, true);
}

ADunkel_GameMode::~ADunkel_GameMode()
{
	Map = nullptr;
	Dunkel = nullptr;
}

void ADunkel_GameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
	FallenWarriorSpawnTime -= _DeltaTime;
	if (FallenWarriorSpawnTime <= 0.0f)
	{
		for (int i = 0; i < 5; i++) {
			AFallenWarrior* FallenWarrior =  GetWorld()->SpawnActor<AFallenWarrior>().get();
			
		}
		FallenWarriorSpawnTime = 30.0f;
	}
}
