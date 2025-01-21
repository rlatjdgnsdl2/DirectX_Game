#pragma once
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/GameInstance.h>

// Ό³Έν :
class PlayerStatus : public UGameInstance, public ISerializObject
{
public:
	std::string Name = "";
	int Level = 0;
	float HP = 60000.0f;
	float MP = 40000.0f;
	float Damage = 999999999999.0f;
};

