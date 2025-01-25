#pragma once
#include "Monster.h"

// Ό³Έν :
class ACQ57 : public AMonster
{
public:
	// constrcuter destructer
	ACQ57();
	virtual ~ACQ57();

	// delete Function
	ACQ57(const ACQ57& _Other) = delete;
	ACQ57(ACQ57&& _Other) noexcept = delete;
	ACQ57& operator=(const ACQ57& _Other) = delete;
	ACQ57& operator=(ACQ57&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	bool bIsKnockBackCollisionSpawn = false;
	float KnockBackCollisionSpawnTime = 1.0f;

	bool bIsPhantomBlowCollisionSpawn = false;
	int PhantomBlowCount = 0;
	float PhantomBlowDelay = 0.1f;
	float PhantomBlowCollisionSpawnTime = 0.1f;

	void StartKnockBack();
	void UpdateKnockBack(float _DeltaTime);

	void KnockBack(UCollision* _Left, UCollision* _Right);
	void PhantomBlow(UCollision* _Left, UCollision* _Right);

	void StartPhantomBlow();
	void UpdatePhantomBlow(float _DeltaTime);






};

