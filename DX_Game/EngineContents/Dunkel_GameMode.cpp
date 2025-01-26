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


