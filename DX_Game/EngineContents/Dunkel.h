#pragma once
#include <EngineCore/Actor.h>
#include "DunkelAnimation.h"

//	Ό³Έν:
class ADunkel :public AActor
{
public:
	ADunkel();
	virtual ~ADunkel();
	ADunkel(const ADunkel& _Other) = delete;
	ADunkel(ADunkel&& _Other) noexcept = delete;
	ADunkel& operator=(const ADunkel& _Other) = delete;
	ADunkel& operator=(ADunkel&& _Other) noexcept = delete;

protected:

private:
	UDunkelAnimation DunkelAnimation;

};

