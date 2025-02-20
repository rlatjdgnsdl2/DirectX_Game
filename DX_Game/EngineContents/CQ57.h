#pragma once
#include "Monster.h"

// ���� :
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
	float CurTime = 0.0f;
	int PrevIndex = 0;
	int CurIndex = 0;
	float StartPosX = 0.0f;
	float TargetPosX = 0.0f;


	void StartKnockBack();
	void UpdateKnockBack(float _DeltaTime);
	void KnockBack(UCollision* _Left, UCollision* _Right);

	void StartPhantomBlow();
	void UpdatePhantomBlow(float _DeltaTime);
	void PhantomBlow(UCollision* _Left, UCollision* _Right);







};

