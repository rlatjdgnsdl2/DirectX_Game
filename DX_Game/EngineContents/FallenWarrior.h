#pragma once
#include "Monster.h"


//	Ό³Έν:
class AFallenWarrior :public AMonster
{
public:
	AFallenWarrior();
	virtual ~AFallenWarrior();
	AFallenWarrior(const AFallenWarrior& _Other) = delete;
	AFallenWarrior(AFallenWarrior&& _Other) noexcept = delete;
	AFallenWarrior& operator=(const AFallenWarrior& _Other) = delete;
	AFallenWarrior& operator=(AFallenWarrior&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:

private:
	UEngineRandom Random;
	class USpriteRenderer* Barrior;

	float NoDamageTime = 5.0f;
	float AttackDelay = 0.5f;
	float WalkTime = 0.0f;

	void StartSpawn() override;
	void UpdateSpawn(float _DeltaTime) override;
	void StartStand() override;
	void UpdateStand(float _DeltaTime) override;
	void StartMove() override;
	void UpdateMove(float _DeltaTime) override;
	void StartAttack() override;
	void UpdateAttack(float _DeltaTime) override;
	void StartDie() override;
	void UpdateDie(float _DeltaTime) override;
};

