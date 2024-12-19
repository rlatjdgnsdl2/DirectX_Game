#include "PreCompile.h"
#include "TempActor.h"
#include <EngineCore/Renderer.h>

 

ATempActor::ATempActor() 
{
	std::shared_ptr<URenderer> NewRenderer = CreateDefaultSubObject<URenderer>();
}

ATempActor::~ATempActor() 
{

}
