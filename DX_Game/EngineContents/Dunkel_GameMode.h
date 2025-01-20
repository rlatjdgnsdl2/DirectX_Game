#pragma once
#include <EngineBase/EngineRandom.h>
#include <EngineCore/GameMode.h>
#include "Dunkel_GUI.h"

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

	void UpdateMapPattern(float _DeltaTime);


protected:

private:
	float FallenWarriorSpawnTime = 0.0f;
	FVector MapSize;
	
	std::shared_ptr<class ADunkel_Map> Map;
	std::shared_ptr<class ADunkel_Boss> Dunkel;
	std::list<class AFallenWarrior*> FallenWarriors;
	std::shared_ptr<UDunkel_GUI> Dunkel_GUI;

	UEngineRandom Random;
	UEngineCamera* MainCamera = nullptr;
	
	


};

