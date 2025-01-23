#pragma once
#include "EngineCore/Actor.h"

//	Ό³Έν:
class ADamageSkinFactory : public AActor
{
public:
	ADamageSkinFactory();
	virtual ~ADamageSkinFactory();
	ADamageSkinFactory(const ADamageSkinFactory& _Other) = delete;
	ADamageSkinFactory(ADamageSkinFactory&& _Other) noexcept = delete;
	ADamageSkinFactory& operator=(const ADamageSkinFactory& _Other) = delete;
	ADamageSkinFactory& operator=(ADamageSkinFactory&& _Other) noexcept = delete;

	void SetDamageInfo(FDamageInfo& _DamageInfo)
	{
		DamageInfo = _DamageInfo;
		HitDelay = DamageInfo.HitDelay;
	}
	void SetSpawnLocation(FVector _SpawnLocation)
	{
		SpawnLocation = _SpawnLocation;
	}
	void Tick(float _DeltaTime) override;
	

protected:

private:
	FDamageInfo DamageInfo;
	FVector SpawnLocation;
	float HitDelay = 0.0f;
	int CurHitCount =0;
	float OffsetY = 0.0f;



};

