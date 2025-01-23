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


}

void ADunkel_GameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
	UpdateMapPattern(_DeltaTime);
	MoveCamera(_DeltaTime);
}

void ADunkel_GameMode::MoveCamera(float _DeltaTime)
{
	FVector CameraPos = MainCamera->GetWorldLocation();  // ���� ī�޶� ��ġ
	FVector PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();  // �÷��̾� ��ġ
	FVector WindowSize = GEngine->GetMainWindow().GetWindowSize();  // ȭ�� ũ�� (����/����)

	// ȭ�� ũ�� ���� ���
	float HalfWindowWidth = WindowSize.X * 0.5f;
	float HalfWindowHeight = WindowSize.Y * 0.5f;

	// �� ��� ��� (�� �߽��� ��������)
	float MapMinX = MapPos.X - MapSize.X * 0.5f + HalfWindowWidth; // ���� ���
	float MapMaxX = MapPos.X + MapSize.X * 0.5f - HalfWindowWidth; // ������ ���
	float MapMinY = MapPos.Y - MapSize.Y * 0.5f + HalfWindowHeight; // �Ʒ��� ���
	float MapMaxY = MapPos.Y + MapSize.Y * 0.5f - HalfWindowHeight; // ���� ���

	// ��ǥ ī�޶� ��ġ�� �÷��̾� ��ġ�� �����ϵ�, �� ��� ������ ����
	float TargetX = UEngineMath::Clamp(PlayerPos.X, MapMinX, MapMaxX);
	float TargetY = UEngineMath::Clamp(PlayerPos.Y, MapMinY, MapMaxY);

	// ���� ī�޶� ��ġ�� ��ǥ ��ġ ���̸� �����Ͽ� �ε巴�� �̵�
	float LerpSpeed = 5.0f;  // ī�޶� �̵� �ӵ�
	FVector SmoothCameraPos = FVector::Lerp(CameraPos, FVector(TargetX, TargetY, CameraPos.Z), _DeltaTime * LerpSpeed);

	// ī�޶� ��ġ ������Ʈ
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
