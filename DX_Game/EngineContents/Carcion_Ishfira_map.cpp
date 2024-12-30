#include "PreCompile.h"
#include "Carcion_Ishfira_map.h"
#include <EngineCore/SpriteRenderer.h>


ACarcion_Ishfira_Map::ACarcion_Ishfira_Map() 
{
	BackRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackRenderer->CreateAnimation("Ishfira", "Ishfira",0,9);
	BackRenderer->ChangeAnimation("Ishfira");

}

ACarcion_Ishfira_Map::~ACarcion_Ishfira_Map() 
{

}
