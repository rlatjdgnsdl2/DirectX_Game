#include "PreCompile.h"
#include "TempActor.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ATempActor::ATempActor()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// �������� �����.
	TempRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TempRenderer->SetSprite("Player.png", 0);

	// �θ� �������� �ʴ� root�� Relative�� Local�̴� 
	// ����� ����. 
	// �θ��� ũ�⿡ ���� ������ ������ �ֱ� �빮�� �Լ��� �������̴�.
	// �θ� ������
	TempRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	TempRenderer->SetupAttachment(RootComponent);




	Child = CreateDefaultSubObject<USpriteRenderer>();
	Child->SetSprite("Player.png", 2);
	Child->SetRelativeLocation({ 100.0f, 0.0f, 0.0f });
	Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
}

ATempActor::~ATempActor()
{
}

void ATempActor::BeginPlay()
{
	AActor::BeginPlay();
}

void ATempActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//AddActorLocation(FVector{ 0.01f, 0.0f, 0.0f });
}