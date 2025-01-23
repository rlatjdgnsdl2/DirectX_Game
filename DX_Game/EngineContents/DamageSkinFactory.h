#pragma once
#include "EngineCore/Actor.h"

//	Ό³Έν:
class DamageSkinFactory : public AActor
{
public:
	DamageSkinFactory();
	virtual ~DamageSkinFactory();
	DamageSkinFactory(const DamageSkinFactory& _Other) = delete;
	DamageSkinFactory(DamageSkinFactory&& _Other) noexcept = delete;
	DamageSkinFactory& operator=(const DamageSkinFactory& _Other) = delete;
	DamageSkinFactory& operator=(DamageSkinFactory&& _Other) noexcept = delete;

	void SetDamageInfo(FDamageInfo& _DamageInfo)
	{
		DamageInfo = _DamageInfo;
		HitDelay = DamageInfo.HitDelay;
	}
	void Tick(float _DeltaTime) override;

protected:

private:
	FDamageInfo DamageInfo;
	float HitDelay = 0.0f;
	int CurHitCount =0;
	float OffsetY = 0.0f;

};

