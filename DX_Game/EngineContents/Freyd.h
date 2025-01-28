#pragma once
#include "Monster.h"

// Ό³Έν :
class AFreyd : public AMonster
{
public:
	// constrcuter destructer
	AFreyd();
	virtual ~AFreyd();

	// delete Function
	AFreyd(const AFreyd& _Other) = delete;
	AFreyd(AFreyd&& _Other) noexcept = delete;
	AFreyd& operator=(const AFreyd& _Other) = delete;
	AFreyd& operator=(AFreyd&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	int PrevIndex = 0;
	int CurIndex = 0;


	void StartShot();
	void UpdateShot(float _DeltaTime);

	int Pattern = 0;
	
	void StartFist();
	void UpdateFist(float _DeltaTime);
	UEngineRandom Random;
	std::vector<float> ShotPosX = { -650.0f, -550.0f, -450.0f, -350.0f , -250.0f , -150.0f , -50.0f , 50.0f , 150.0f , 250.0f , 350.0f , 450.0f , 550.0f , 650.0f };

	void Fist(class UCollision* _Left, class UCollision* _Right);


};

