#pragma once
#include "PlayerFunction.h"



//	����:
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
		FSM.Update(_DeltaTime);
	}

	void ChangeState(ESkill_Frame _Frame)
	{
		FSM.ChangeState(_Frame);
	};


protected:
	std::map<std::string, class USpriteRenderer*> SpriteRenderers;
	class UMyCollision* Collision;
	UFSMStateManager FSM;
	FDamageInfo DamageInfo;
	float UseMp;

private:

};

