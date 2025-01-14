#pragma once
#include "AnimationManager.h"
//	����:
class UDunkelAnimation : public UAnimationManager
{
public:
	UDunkelAnimation();
	virtual ~UDunkelAnimation();
	UDunkelAnimation(const UDunkelAnimation& _Other) = delete;
	UDunkelAnimation(UDunkelAnimation&& _Other) noexcept = delete;
	UDunkelAnimation& operator=(const UDunkelAnimation& _Other) = delete;
	UDunkelAnimation& operator=(UDunkelAnimation&& _Other) noexcept = delete;

	virtual void Init() override;

protected:

private:

};

