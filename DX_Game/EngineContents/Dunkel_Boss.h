#pragma once
#include "Boss.h"

//	Ό³Έν:
class ADunkel_Boss :public ABoss
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

	void ChangeState(EDunkelAnim_State _State) 
	{
		FSM.ChangeState(_State);
	};


protected:

private:
	float CollisonSpawnTime = 0.0f;
	float SlashCoolTime = 15.0f;
	float SwordCoolTime = 30.0f;
	float MeteoCoolTime = 25.0f;
	float StandTime = 2.0f;

	std::vector<int> EliteMonsterList {0,1,2,3,4};
	std::list<class AFallenWarrior*> FallenWarriorList;

	UEngineRandom Random;
	
	bool bIsScopePlayer = false;
	bool bIsAttacking = false;

	void CheckDir();

	void SpawnEliteMonster();

	void StartSpawn() override;
	void UpdateSpawn(float _DeltaTime) override;

	void StartStand() override;
	void UpdateStand(float _DeltaTime) override;

	void StartDie() override;
	void UpdateDie(float _DeltaTime) override;


	void StartForce();
	void UpdateForce(float _DeltaTime);

	void StartKnockback();
	void UpdateKnockback(float _DeltaTime);

	void StartMeteo();
	void UpdateMeteo(float _DeltaTime);
	void SpawnMeteo();

	void StartSlash_Start();
	void UpdateSlash_Start(float _DeltaTime);

	void StartSlash_End();
	void UpdateSlash_End(float _DeltaTime);


	void StartSword();
	void UpdateSword(float _DeltaTime);
	void SpawnSwordPower();

	void StartUp();
	void UpdateUp(float _DeltaTime);

	void StartDown();
	void UpdateDown(float _DeltaTime);


	void UpdateMapPattern(float _DeltaTime);

	std::vector<float> FallenWarriorSpawnPosX;
	float FallenWarriorSpawnTime = 5.0f;


	std::vector<float> PillarLightPosX;
	float PillarLightSpawnTime = 10.0f;
	int PillarLightSpawnCount = 0;
	int PillarLightCount = 0;
};

