#pragma once
#include "Monster.h"

//	Ό³Έν:
class ADunkel_Boss :public AMonster
{
public:
	ADunkel_Boss();
	virtual ~ADunkel_Boss();
	ADunkel_Boss(const ADunkel_Boss& _Other) = delete;
	ADunkel_Boss(ADunkel_Boss&& _Other) noexcept = delete;
	ADunkel_Boss& operator=(const ADunkel_Boss& _Other) = delete;
	ADunkel_Boss& operator=(ADunkel_Boss&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:

private:
	float CurTime = 0.0f;


};

