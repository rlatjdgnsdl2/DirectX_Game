#include "PreCompile.h"
#include "TempActor.h"
#include <EngineCore/Renderer.h>

ATempActor::ATempActor()
{
	// 랜더러를 만든다.
	TempRenderer = CreateDefaultSubObject<URenderer>();

	SetActorRelativeScale3D({ 100.0f, 100.0f, 1.0f });

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
	AddActorLocation(FVector{ 0.01f, 0.0f, 0.0f });
}