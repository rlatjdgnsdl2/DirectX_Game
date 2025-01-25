#include "PreCompile.h"
#include "Dunkel_GameMode.h"



void ADunkel_GameMode::ResLoad() 
{
	//	Dunkel 리소스로드
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
	
	//	로드된 리소스 Sprite로 만들기
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\Boss\\Boss_Dunkel");

		// Map
		Dir.Append("DunkelMapBackGround");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("DunkelMapObject_Sphere");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("DunkelMapObject_Stone");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("PillarLight");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();


		// Dunkel
		Dir.Append("Dunkel\\Dunkel_Die");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Down");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Force");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_KnockBack");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Meteo");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Meteo_Effect_End");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Meteo_Effect_Start");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Meteo_Effect_Update");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Slash_End");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Slash_Start");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Spawn");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Stand");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_SwordPower");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_SwordPower_Effect");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Dunkel_Up");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

	}

	//	FallenWarrior
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

		Dir.Append("FallenWarrior_Hit");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("FallenWarrior_Barrior");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();
	}

	// Elite Monster
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\Boss\\Boss_Dunkel\\Elite_Monster\\Chain_Effetc");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("CQ57\\CQ57_KnockBack");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("CQ57_PhantomBlow");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();
		Dir.BackDir();

		Dir.Append("Elite_Spawn");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Freyd\\Freyd_HeadShoot");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Freyd_HeadShoot_Effect");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Freyd_Inlage");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();
		Dir.BackDir();

		Dir.Append("Jurai\\Jurai_Chain");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Jurai_Sniping");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Jurai_Sniping_Effect");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Jurai_Sniping_Hit");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();
		Dir.BackDir();


		Dir.Append("Khaliain\\Khaliain_Chain");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Khaliain_Chain_Effect");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Khaliain_MagicSphere");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Khaliain_MagicSphere_Effect");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Khaliain_MagicSphere_hit");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();
		Dir.BackDir();

		Dir.Append("Mogadin\\Mogadin_Chain");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();

		Dir.Append("Mogadin_Slash");
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		Dir.BackDir();





	}


}