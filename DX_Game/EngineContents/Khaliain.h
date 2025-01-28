#pragma once
#include "Monster.h"

// Ό³Έν :
class AKhaliain : public AMonster
{
public:
	// constrcuter destructer
	AKhaliain();
	virtual ~AKhaliain();

	// delete Function
	AKhaliain(const AKhaliain& _Other) = delete;
	AKhaliain(AKhaliain&& _Other) noexcept = delete;
	AKhaliain& operator=(const AKhaliain& _Other) = delete;
	AKhaliain& operator=(AKhaliain&& _Other) noexcept = delete;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	std::vector<float> ChainPosX = { -650.0f, -550.0f, -450.0f, -350.0f , -250.0f , -150.0f , -50.0f , 50.0f , 150.0f , 250.0f , 350.0f , 450.0f , 550.0f , 650.0f };
	int PrevIndex = 0;
	int CurIndex = 0;

	int Pattern = 0;
	UEngineRandom Random;

	void StartMagic();
	void UpdateMagic(float _DeltaTime);

	void StartChain();
	void UpdateChain(float _DeltaTime);
};

