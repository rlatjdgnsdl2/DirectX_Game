#pragma once
#include "Bar.h"

//	Ό³Έν:
class UPlayerHpBarEffect :public UBar
{
public:
	UPlayerHpBarEffect();
	virtual ~UPlayerHpBarEffect();
	UPlayerHpBarEffect(const UPlayerHpBarEffect& _Other) = delete;
	UPlayerHpBarEffect(UPlayerHpBarEffect&& _Other) noexcept = delete;
	UPlayerHpBarEffect& operator=(const UPlayerHpBarEffect& _Other) = delete;
	UPlayerHpBarEffect& operator=(UPlayerHpBarEffect&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
	virtual void BarLerp(float _StartPercent, float _EndPercent, float _DeltaTime, bool& _bIsChange) override;

protected:

private:

};

