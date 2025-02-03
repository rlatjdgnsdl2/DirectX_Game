#pragma once
#include "Skill.h"

//	Ό³Έν:
class ASkill_DefyingFate : public ASkill
{
public:
	ASkill_DefyingFate();
	virtual ~ASkill_DefyingFate();
	ASkill_DefyingFate(const ASkill_DefyingFate& _Other) = delete;
	ASkill_DefyingFate(ASkill_DefyingFate&& _Other) noexcept = delete;
	ASkill_DefyingFate& operator=(const ASkill_DefyingFate& _Other) = delete;
	ASkill_DefyingFate& operator=(ASkill_DefyingFate&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	virtual void SetActiveTrue() override;
	virtual void SetActiveFalse() override;

protected:

private:
	float CurTime = 0.0f;
	void Start_DefyingFate_Start();
	void Update_DefyingFate_Start(float _DeltaTime);

	void Start_DefyingFate_Update();
	void Update_DefyingFate_Update(float _DeltaTime);

	void Start_DefyingFate_End();
	void Update_DefyingFate_End(float _DeltaTime);

	
};

