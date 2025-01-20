#include "PreCompile.h"

#include <EngineCore/EngineGUI.h>

#include "Dunkel_GameMode.h"

#include "Dunkel_Map.h"
#include "Dunkel_Boss.h"

#include "FallenWarrior.h"



ADunkel_GameMode::ADunkel_GameMode()
{
	ResLoad();
	
	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->CreateCollisionProfile("PlayerSkill");
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Boss");
	GetWorld()->CreateCollisionProfile("BossAttack");
	GetWorld()->CreateCollisionProfile("UI");
	GetWorld()->CreateCollisionProfile("EndArea");

	Map = GetWorld()->SpawnActor<ADunkel_Map>();
	Dunkel = GetWorld()->SpawnActor<ADunkel_Boss>();

	Dunkel_GUI = UEngineGUI::CreateGUIWindow<UDunkel_GUI>("Dunkel_GUI");
	
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
	Dunkel_GUI->SetActive(true);
	
}

void ADunkel_GameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
	UpdateMapPattern(_DeltaTime);
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

void ADunkel_GameMode::UpdateMapPattern(float _DeltaTime)
{
	FallenWarriorSpawnTime -= _DeltaTime;
	if (FallenWarriorSpawnTime <= 0.0f)
	{
		for (int i = 0; i < 5; i++) {
			AFallenWarrior* FallenWarrior = GetWorld()->SpawnActor<AFallenWarrior>().get();
			FallenWarrior->SetActorLocation(FVector(Random.Randomfloat(-MapSize.hX(), MapSize.hX()), 0.0f));
			FallenWarriors.push_back(FallenWarrior);

		}
		FallenWarriorSpawnTime = 30.0f;
	}
}
