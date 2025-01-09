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

	virtual void SetActive(bool _Value) override
	{
		UObject::SetActive(_Value);
		ChangeState(Skill_Frame::Start);
	}

	

protected:

private:
	

};

