#pragma once
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/GameInstance.h>

// Ό³Έν :
class MyGameInstance : public UGameInstance, public ISerializObject
{
public:
	FPlayerStatus PlayerStatus;
	
};

