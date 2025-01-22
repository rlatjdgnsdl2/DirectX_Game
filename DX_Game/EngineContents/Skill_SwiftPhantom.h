#pragma once
#include "Skill.h"

//	Ό³Έν:
class ASkill_SwiftPhantom : public ASkill
{
public:
	ASkill_SwiftPhantom();
	virtual ~ASkill_SwiftPhantom();
	ASkill_SwiftPhantom(const ASkill_SwiftPhantom& _Other) = delete;
	ASkill_SwiftPhantom(ASkill_SwiftPhantom&& _Other) noexcept = delete;
	ASkill_SwiftPhantom& operator=(const ASkill_SwiftPhantom& _Other) = delete;
	ASkill_SwiftPhantom& operator=(ASkill_SwiftPhantom&& _Other) noexcept = delete;

	virtual void SetActiveTrue() override;
	
protected:

private:
	void StartJump();
	void UpdateJump(float _DeltaTime);
	void StartDoubleJump();
	void UpdateDoubleJump(float _DeltaTime);
	void StartTripleJump();
	void UpdateTripleJump(float _DeltaTime);
};

