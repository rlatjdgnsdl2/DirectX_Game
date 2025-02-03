#pragma once
#include "Skill.h"


//	Ό³Έν:
class ASkill_RiftBreak : public ASkill
{
public:
	ASkill_RiftBreak();
	virtual ~ASkill_RiftBreak();
	ASkill_RiftBreak(const ASkill_RiftBreak& _Other) = delete;
	ASkill_RiftBreak(ASkill_RiftBreak&& _Other) noexcept = delete;
	ASkill_RiftBreak& operator=(const ASkill_RiftBreak& _Other) = delete;
	ASkill_RiftBreak& operator=(ASkill_RiftBreak&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	virtual void SetActiveTrue() override;
	virtual void SetActiveFalse() override;

protected:

private:
	void StartRiftBreak();
	void UpdateRiftBreak(float _DeltaTime);
};

