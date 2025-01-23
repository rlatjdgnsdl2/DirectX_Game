#pragma once
#include "Bar.h"

//	Ό³Έν:
class UPlayerMpBar : public UBar
{
public:
	UPlayerMpBar();
	virtual ~UPlayerMpBar();
	UPlayerMpBar(const UPlayerMpBar& _Other) = delete;
	UPlayerMpBar(UPlayerMpBar&& _Other) noexcept = delete;
	UPlayerMpBar& operator=(const UPlayerMpBar& _Other) = delete;
	UPlayerMpBar& operator=(UPlayerMpBar&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;

protected:

private:

};

