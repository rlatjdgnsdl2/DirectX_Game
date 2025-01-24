#pragma once
#include "Bar.h"

//	Ό³Έν:
class UPlayerMpBarEffect :public UBar
{
public:
	UPlayerMpBarEffect();
	virtual ~UPlayerMpBarEffect();
	UPlayerMpBarEffect(const UPlayerMpBarEffect& _Other) = delete;
	UPlayerMpBarEffect(UPlayerMpBarEffect&& _Other) noexcept = delete;
	UPlayerMpBarEffect& operator=(const UPlayerMpBarEffect& _Other) = delete;
	UPlayerMpBarEffect& operator=(UPlayerMpBarEffect&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;
	void BarLerp(float _StartPercent, float _EndPercent, float _f, bool& _bIsChange) override;

protected:

private:

};

