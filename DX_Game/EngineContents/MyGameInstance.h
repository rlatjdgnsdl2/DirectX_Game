#pragma once
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/GameInstance.h>
#include "ContentsStruct.h"






// Ό³Έν :
class MyGameInstance : public UGameInstance, public ISerializObject
{
public:
	FPlayerStatus PlayerStatus;
	FPlayerLogic PlayerLogic;
};

