#pragma once
#include "AnimationManager.h"



//	����:
class UPlayerAnimation : public UAnimationManager
{
public:
	UPlayerAnimation();
	virtual ~UPlayerAnimation();
	UPlayerAnimation(const UPlayerAnimation& _Other) = delete;
	UPlayerAnimation(UPlayerAnimation&& _Other) noexcept = delete;
	UPlayerAnimation& operator=(const UPlayerAnimation& _Other) = delete;
	UPlayerAnimation& operator=(UPlayerAnimation&& _Other) noexcept = delete;

	virtual void Init() override;
	
protected:

private:

};

