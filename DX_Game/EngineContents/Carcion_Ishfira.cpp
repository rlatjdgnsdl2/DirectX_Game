#include "PreCompile.h"
#include "Carcion_Ishfira.h"
#include "Carcion_Ishfira_map.h"


ACarcion_Ishfira::ACarcion_Ishfira() 
{
	Carcion_Ishfira_Map = GetWorld()->SpawnActor<ACarcion_Ishfira_Map>();
}

ACarcion_Ishfira::~ACarcion_Ishfira() 
{
	Carcion_Ishfira_Map = nullptr;
}
