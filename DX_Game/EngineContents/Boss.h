#pragma once
#include "Monster.h"

//	Ό³Έν:
class ABoss :public AMonster
{
public:
	ABoss();
	virtual ~ABoss();
	ABoss(const ABoss& _Other) = delete;
	ABoss(ABoss&& _Other) noexcept = delete;
	ABoss& operator=(const ABoss& _Other) = delete;
	ABoss& operator=(ABoss&& _Other) noexcept = delete;

protected:

private:

};

