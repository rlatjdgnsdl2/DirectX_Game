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
	void SetSpawnLocation();
	

	void SetMonsterCollision(class UCollision* _Monster)
	{
		MonsterColl = _Monster;
		SetSpawnLocation();
	}
	void Tick(float _DeltaTime) override;
	

protected:

private:
	UEngineRandom Random;
	FDamageInfo DamageInfo;
	FVector SpawnLocation;
	float HitDelay = 0.0f;
	int CurHitCount =0;

	class UCollision* MonsterColl = nullptr;


	int CurCycle = 0;

	float OffsetY = 0.0f;



};

