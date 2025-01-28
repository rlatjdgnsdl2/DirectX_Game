#pragma once
#include "Monster.h"


// Ό³Έν :
class AJurai : public AMonster
{
public:
	// constrcuter destructer
	AJurai();
	virtual ~AJurai();

	// delete Function
	AJurai(const AJurai& _Other) = delete;
	AJurai(AJurai&& _Other) noexcept = delete;
	AJurai& operator=(const AJurai& _Other) = delete;
	AJurai& operator=(AJurai&& _Other) noexcept = delete;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	int PrevIndex = 0;
	int CurIndex = 0;

	int Pattern = 0;
	UEngineRandom Random;

	void StartSniping();
	void UpdateSniping(float _DeltaTime);

	void StartChain();
	void UpdateChain(float _DeltaTime);


};

