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

	virtual void SetActiveTrue() override;
	
	

protected:

private:
	void StartUltimateDrivePrev();
	void UpdateUltimateDrivePrev(float _DeltaTime);
	void StartUltimateDriveKeyDown();
	void UpdateUltimateDriveKeyDown(float _DeltaTime);
	void StartUltimateDriveEnd();
	void UpdateUltimateDriveEnd(float _DeltaTime);
	

	

};

