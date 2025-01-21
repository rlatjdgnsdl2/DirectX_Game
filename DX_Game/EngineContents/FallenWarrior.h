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
	UFSMStateManager AnimaionFSM;

	float WalkTime = 0.0f;
	int Dir = 0;

	class USpriteRenderer* SpriteRenderer;
	class UCollision* Collision;
	class UCollision* AttackCollision;
	class UCollision* ScopeCollision;

	
	

	void StartSpawn();
	void UpdateSpawn(float _DeltaTime);
	void StartStand();
	void UpdateStand(float _DeltaTime);
	void StartMove();
	void UpdateMove(float _DeltaTime);
	void StartAttack();
	void UpdateAttack(float _DeltaTime);
	void StartDie();
	void UpdateDie(float _DeltaTime);
	void StartHit();
	void UpdateHit(float _DeltaTime);

};

