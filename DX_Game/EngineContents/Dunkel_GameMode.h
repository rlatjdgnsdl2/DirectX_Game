#pragma once
#include <EngineBase/EngineRandom.h>
#include <EngineCore/GameMode.h>

//	Ό³Έν:
class ADunkel_GameMode : public AGameMode
{
public:
	ADunkel_GameMode();
	virtual ~ADunkel_GameMode();
	ADunkel_GameMode(const ADunkel_GameMode& _Other) = delete;
	ADunkel_GameMode(ADunkel_GameMode&& _Other) noexcept = delete;
	ADunkel_GameMode& operator=(const ADunkel_GameMode& _Other) = delete;
	ADunkel_GameMode& operator=(ADunkel_GameMode&& _Other) noexcept = delete;

	void ResLoad();

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	void MoveCamera(float _DeltaTime);



protected:

private:
	void UpdateMapPattern(float _DeltaTime);

	std::vector<float> FallenWarriorSpawnPosX;
	float FallenWarriorSpawnTime = 5.0f;
	float FallenWarriorSpawnZ = 10.0f;

	std::vector<float> PillarLightPosX;
	float PillarLightSpawnTime = 10.0f;
	float PillarLightSpawnZ = 10.0f;
	int PillarLightSpawnCount = 0;
	int PillarLightCount = 0;



	FVector MapSize;
	FVector MapPos;

	class ADunkel_Map* Map;
	class ADunkel_Boss* BossDunkel;
	class UDunkel_GUI* Dunkel_GUI;

	UEngineRandom Random;
	UEngineCamera* MainCamera = nullptr;
	
	


};

