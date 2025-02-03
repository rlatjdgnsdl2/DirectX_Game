#include "PreCompile.h"

#include <EngineCore/EngineGUI.h>

#include "Dunkel_GameMode.h"

#include "Dunkel_Map.h"
#include "Dunkel_Boss.h"
#include "Dunkel_GUI.h"




ADunkel_GameMode::ADunkel_GameMode()
{
	ResLoad();

	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->CreateCollisionProfile("PlayerSkill");

	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("MonsterAttack");

	GetWorld()->CreateCollisionProfile("Boss");
	GetWorld()->CreateCollisionProfile("BossAttack");

	GetWorld()->CreateCollisionProfile("EliteMonster");

	GetWorld()->CreateCollisionProfile("Scope");
	
	GetWorld()->CreateCollisionProfile("EndArea");

	Map = GetWorld()->SpawnActor<ADunkel_Map>().get();
	BossDunkel = GetWorld()->SpawnActor<ADunkel_Boss>().get();

	

	Dunkel_GUI = UEngineGUI::CreateGUIWindow<UDunkel_GUI>("Dunkel_GUI").get();
	Dunkel_GUI->Dunkel = BossDunkel;

	GetWorld()->LinkCollisionProfile("PlayerSkill", "Monster");
	GetWorld()->LinkCollisionProfile("PlayerSkill", "Boss");

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


