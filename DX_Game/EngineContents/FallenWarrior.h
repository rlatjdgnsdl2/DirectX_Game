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

	void Force()
	{
		AttackDamage = 0.1f;
	}
	void EndForce()
	{
		AttackDamage = 0.05f;
	}


protected:

private:
	UEngineRandom Random;
	class USpriteRenderer* BarriorRenderer;

	float NoDamageTime = 5.0f;
	float SelfDestroyTime = 30.0f;

	float WalkTime = 2.0f;

	float AttackDamage = 0.05f;
	bool bIsAttackCollisionActive = false;
	float AttackCollisionActiveTime = 0.0f;

	bool bIsSelfDestroyCollisionActive = false;
	float SelfDestroyCollisionActiveTime = 0.0f;

	
	

	void StartSpawn() override;
	void UpdateSpawn(float _DeltaTime) override;
	void StartStand() override;
	void UpdateStand(float _DeltaTime) override;
	void StartMove() override;
	void UpdateMove(float _DeltaTime) override;

	void StartAttack() override;
	void UpdateAttack(float _DeltaTime) override;
	void Attack(class UCollision* _Left, class UCollision* _Right);

	void StartDie() override;
	void UpdateDie(float _DeltaTime) override;

	void StartSelfDestroy();
	void UpdateSelfDestroy(float _DeltaTime);
	void SelfDestroy(class UCollision* _Left, class UCollision* _Right);
};

