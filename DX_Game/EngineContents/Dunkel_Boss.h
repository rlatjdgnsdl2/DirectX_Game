#pragma once
#include "Monster.h"

//	Ό³Έν:
class ADunkel_Boss :public AMonster
{
public:
	ADunkel_Boss();
	virtual ~ADunkel_Boss();
	ADunkel_Boss(const ADunkel_Boss& _Other) = delete;
	ADunkel_Boss(ADunkel_Boss&& _Other) noexcept = delete;
	ADunkel_Boss& operator=(const ADunkel_Boss& _Other) = delete;
	ADunkel_Boss& operator=(ADunkel_Boss&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;


protected:

private:
	float CurTime = 0.0f;

	void StartDie();
	void UpdateDie(float _DeltaTime);

	void StartForce();
	void UpdateForce(float _DeltaTime);

	void StartKnockback();
	void UpdateKnockback(float _DeltaTime);

	void StartMeteo();
	void UpdateMeteo(float _DeltaTime);

	void StartSlash_Start();
	void UpdateSlash_Start(float _DeltaTime);

	void StartSlash_End();
	void UpdateSlash_End(float _DeltaTime);

	void StartSpawn();
	void UpdateSpawn(float _DeltaTime);

	void StartStand();
	void UpdateStand(float _DeltaTime);

	void StartSword();
	void UpdateSword(float _DeltaTime);

	void StartUp();
	void UpdateUp(float _DeltaTime);

	void StartDown();
	void UpdateDown(float _DeltaTime);



};

