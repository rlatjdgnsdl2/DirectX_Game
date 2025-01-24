#include "PreCompile.h"

#include <EngineCore/EngineGUI.h>

#include "Dunkel_GameMode.h"

#include "Dunkel_Map.h"
#include "Dunkel_Boss.h"
#include "Dunkel_GUI.h"
#include "FallenWarrior.h"
#include "PillarLight.h"



ADunkel_GameMode::ADunkel_GameMode()
{
	ResLoad();

	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->CreateCollisionProfile("PlayerSkill");
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("MonsterAttack");
	GetWorld()->CreateCollisionProfile("Boss");
	GetWorld()->CreateCollisionProfile("BossAttack");
	GetWorld()->CreateCollisionProfile("Scope");
	GetWorld()->CreateCollisionProfile("UI");
	GetWorld()->CreateCollisionProfile("EndArea");

	GetWorld()->LinkCollisionProfile("MonsterAttack", "Player");


	Map = GetWorld()->SpawnActor<ADunkel_Map>().get();
	BossDunkel = GetWorld()->SpawnActor<ADunkel_Boss>().get();

	FallenWarriorSpawnPosX = { -150.0f,-50.0f,50.0f,150.0f };
	PillarLightPosX = { -520.0f,-395.0f, -270.0f,-145.0f,-20.0f,105.0f, 230.0f,355.0f,480.0f };

	Dunkel_GUI = UEngineGUI::CreateGUIWindow<UDunkel_GUI>("Dunkel_GUI").get();
	Dunkel_GUI->Dunkel = BossDunkel;



}

ADunkel_GameMode::~ADunkel_GameMode()
{

}

void ADunkel_GameMode::BeginPlay()
{
	AGameMode::BeginPlay();
	MapSize = Map->GetBackRenderer()->GetWorldScale3D();
	MapPos = Map->GetBackRenderer()->GetWorldLocation();
	MainCamera = GetWorld()->GetMainCamera()->GetCameraComponent().get();
	MainCamera->SetZSort(0, true);
	Dunkel_GUI->SetActive(true);
	GetWorld()->DebugOn();


}

void ADunkel_GameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
	UpdateMapPattern(_DeltaTime);
	MoveCamera(_DeltaTime);
}

void ADunkel_GameMode::MoveCamera(float _DeltaTime)
{
	FVector CameraPos = MainCamera->GetWorldLocation();  // 현재 카메라 위치
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();  // 플레이어 위치
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();  // 화면 크기 (가로/세로)

	// 화면 크기 절반 계산
	float HalfWindowWidth = WindowSize.X * 0.5f;
	float HalfWindowHeight = WindowSize.Y * 0.5f;

	// 맵 경계 계산 (맵 중심을 기준으로)
	float MapMinX = MapPos.X - MapSize.X * 0.5f + HalfWindowWidth; // 왼쪽 경계
	float MapMaxX = MapPos.X + MapSize.X * 0.5f - HalfWindowWidth; // 오른쪽 경계
	float MapMinY = MapPos.Y - MapSize.Y * 0.5f + HalfWindowHeight; // 아래쪽 경계
	float MapMaxY = MapPos.Y + MapSize.Y * 0.5f - HalfWindowHeight; // 위쪽 경계

	// 목표 카메라 위치를 플레이어 위치로 설정하되, 맵 경계 안으로 제한
	float TargetX = UEngineMath::Clamp(PlayerPos.X, MapMinX, MapMaxX);
	float TargetY = UEngineMath::Clamp(PlayerPos.Y, MapMinY, MapMaxY);

	// 현재 카메라 위치와 목표 위치 사이를 보간하여 부드럽게 이동
	float LerpSpeed = 5.0f;  // 카메라 이동 속도
	FVector SmoothCameraPos = FVector::Lerp(CameraPos, FVector(TargetX, TargetY, CameraPos.Z), _DeltaTime * LerpSpeed);

	// 카메라 위치 업데이트
	MainCamera->SetWorldLocation(SmoothCameraPos);
}

void ADunkel_GameMode::UpdateMapPattern(float _DeltaTime)
{
	FallenWarriorSpawnTime -= _DeltaTime;
	PillarLightSpawnTime -= _DeltaTime;

	// FallenWarrior
	if (FallenWarriorSpawnTime <= 0.0f)
	{
		for (int i = 0; i < 2; i++) {
			AFallenWarrior* FallenWarrior = GetWorld()->SpawnActor<AFallenWarrior>().get();
			FallenWarrior->SetActorLocation(FVector(BossDunkel->GetActorLocation().X + FallenWarriorSpawnPosX[i], 0.0f/*FallenWarriorSpawnZ*/));
			FallenWarriorSpawnZ += 10.0f;
		}
		FallenWarriorSpawnZ = 10.0f;
		FallenWarriorSpawnTime = 30000.0f;
	}

	// PillarLight
	if (PillarLightSpawnTime <= 0.0f) {
		int Index = Random.RandomInt(0, PillarLightPosX.size() - 1);
		if (PillarLightSpawnCount < 3)
		{
			if (PillarLightCount < 4)
			{
				APillarLight* PillarLight = GetWorld()->SpawnActor<APillarLight>().get();
				PillarLight->SetActorLocation(FVector(PillarLightPosX[Index], 0, PillarLightSpawnZ));
				PillarLightCount++;
				PillarLightSpawnZ += 10.0f;
				PillarLightSpawnTime = 1.0f;
			}
			else
			{
				PillarLightCount = 0;
				PillarLightSpawnCount++;
				PillarLightSpawnZ = 10.0f;
				PillarLightSpawnTime = 10.0f;
			}
		}
		else
		{
			PillarLightCount = 0;
			PillarLightSpawnCount = 0;
			PillarLightSpawnTime = 20.0f;
		}
	}
}
