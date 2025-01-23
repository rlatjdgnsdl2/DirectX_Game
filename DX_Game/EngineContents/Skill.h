#pragma once
#include "PlayerFunction.h"



//	Ό³Έν:
class ASkill : public APlayerFunction
{
public:
	ASkill();
	virtual ~ASkill();
	ASkill(const ASkill& _Other) = delete;
	ASkill(ASkill&& _Other) noexcept = delete;
	ASkill& operator=(const ASkill& _Other) = delete;
	ASkill& operator=(ASkill&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;


	void Update(float _DeltaTime)
	{
		FrameState.Update(_DeltaTime);
	}

	void ChangeState(Skill_Frame _Frame)
	{
		FrameState.ChangeState(_Frame);
	};


protected:
	UFSMStateManager FrameState;
	std::map<std::string, class USpriteRenderer*> SpriteRenderers;
	class UMyCollision* Collision;
	FDamageInfo DamageInfo;
	float UseMp;

private:

};

