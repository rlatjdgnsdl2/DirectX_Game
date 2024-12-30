#pragma once
#include <EngineCore/ActorComponent.h>

//	Ό³Έν:
class UPlayerStat : public UActorComponent
{
public:
	UPlayerStat();
	virtual ~UPlayerStat();
	UPlayerStat(const UPlayerStat& _Other) = delete;
	UPlayerStat(UPlayerStat&& _Other) noexcept = delete;
	UPlayerStat& operator=(const UPlayerStat& _Other) = delete;
	UPlayerStat& operator=(UPlayerStat&& _Other) noexcept = delete;

protected:

private:
	float Hp;
	float Mp;
	

};

