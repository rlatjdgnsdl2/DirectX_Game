#pragma once
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/GameInstance.h>

// ���� :
class MyGameInstance : public UGameInstance, public ISerializObject
{
public:
	FPlayerStatus PlayerStatus;
	
};

