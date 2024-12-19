#include "PreCompile.h"
#include "TempPawn.h"
#include <EngineCore/Renderer.h>
#include <memory>

ATempPawn::ATempPawn() 
{
	
}

ATempPawn::~ATempPawn() 
{

}

void ATempPawn::BeginPlay()
{
	AActor::BeginPlay();
}

void ATempPawn::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
