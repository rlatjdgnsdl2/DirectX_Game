#include "PreCompile.h"
#include "Carcion_Ishfira_map.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ACarcion_Ishfira_Map::ACarcion_Ishfira_Map() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	BackRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackRenderer->SetupAttachment(RootComponent);
	BackRenderer->AddRelativeLocation(FVector(0.0f, 0.0f, 100.0f));


	BackRenderer->CreateAnimation("Ishfira", "Ishfira",0,9);
	BackRenderer->ChangeAnimation("Ishfira");
	

}

ACarcion_Ishfira_Map::~ACarcion_Ishfira_Map() 
{

}
