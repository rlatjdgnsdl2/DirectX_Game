#pragma once
#include "Skill.h"



//	Ό³Έν:
class ASkill_UltimateDrive : public ASkill
{
public:
	ASkill_UltimateDrive();
	virtual ~ASkill_UltimateDrive();
	ASkill_UltimateDrive(const ASkill_UltimateDrive& _Other) = delete;
	ASkill_UltimateDrive(ASkill_UltimateDrive&& _Other) noexcept = delete;
	ASkill_UltimateDrive& operator=(const ASkill_UltimateDrive& _Other) = delete;
	ASkill_UltimateDrive& operator=(ASkill_UltimateDrive&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	void ChangeState(Skill_Frame _Frame) 
	{
		FrameState.ChangeState(_Frame);
	};

protected:

private:
	UFSMStateManager FrameState;
	std::shared_ptr<class UTimeEventComponent> TimeEvent;
};

