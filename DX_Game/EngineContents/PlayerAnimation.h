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
	bool CheckAnimNode(PAnimation_State _CurAnimState, PAnimation_State _NextAnimState);
	
protected:

private:
	std::unordered_map<PAnimation_State, std::list<PAnimation_State>> AnimationNode;
	
};

