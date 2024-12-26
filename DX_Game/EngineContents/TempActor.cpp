#include "PreCompile.h"
#include "TempActor.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ATempActor::ATempActor()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 랜더러를 만든다.
	TempRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TempRenderer->SetSprite("Player.png", 0);

	// 부모가 존재하지 않는 root는 Relative든 Local이던 
	// 결과는 같다. 
	// 부모의 크기에 내가 영향을 받을수 있기 대문에 함수가 나뉜것이다.
	// 부모가 없으면
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