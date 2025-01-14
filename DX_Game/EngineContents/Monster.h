#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class AMonster : public AActor
{
public:
	AMonster();
	virtual ~AMonster();
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

protected:

private:
	

};

