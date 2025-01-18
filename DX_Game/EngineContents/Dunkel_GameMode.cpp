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
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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

	
}

ADunkel_GameMode::~ADunkel_GameMode()
{
	Map = nullptr;
	Dunkel = nullptr;
}

void ADunkel_GameMode::BeginPlay()
{
	AGameMode::BeginPlay();
	MapSize = Map->GetBackRenderer()->GetWorldScale3D();
	MainCamera = GetWorld()->GetMainCamera()->GetCameraComponent().get();
	MainCamera->SetZSort(0, true);
	
}

void ADunkel_GameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
	FallenWarriorSpawnTime -= _DeltaTime;
	if (FallenWarriorSpawnTime <= 0.0f)
	{
		/*for (int i = 0; i < 5; i++) {
			AFallenWarrior* FallenWarrior =  GetWorld()->SpawnActor<AFallenWarrior>().get();
			
		}*/
		FallenWarriorSpawnTime = 30.0f;
	}
	MoveCamera(_DeltaTime);
}

void ADunkel_GameMode::MoveCamera(float _DeltaTime)
{
	FVector CameraPos = MainCamera->GetWorldLocation();
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
	if (true) {
		MainCamera->SetWorldLocation(FVector(PlayerPos.X, PlayerPos.Y, CameraPos.Z));
	}
}
