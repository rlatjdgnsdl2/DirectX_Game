#pragma once
#include <EngineBase/EngineSerializer.h>

// Ό³Έν :
class PlayerStat : public ISerializObject
{
public:
	std::string Name = "";

	int Level = 0;
	float EXP = 0.0f;

	float HP = 0.0f;
	float MP = 0.0f;

	float STR = 0.0f;
	float DEX = 0.0f;
	float INT = 0.0f;
	float LUK = 0.0f;

};

