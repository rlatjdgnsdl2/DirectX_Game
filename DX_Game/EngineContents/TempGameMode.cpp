#include "PreCompile.h"
#include "TempGameMode.h"

#include <EngineCore/Level.h>
#include "TempActor.h"


ATempGameMode::ATempGameMode() 
{
	GetWorld()->SpawnActor<ATempActor>();
}

ATempGameMode::~ATempGameMode() 
{

}
