#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineRandom.h>

//	����:
class ADunkel_GameMode : public AGameMode
{
public:
	ADunkel_GameMode();
	virtual ~ADunkel_GameMode();
	ADunkel_GameMode(const ADunkel_GameMode& _Other) = delete;
	ADunkel_GameMode(ADunkel_GameMode&& _Other) noexcept = delete;
	ADunkel_GameMode& operator=(const ADunkel_GameMode& _Other) = delete;
	ADunkel_GameMode& operator=(ADunkel_GameMode&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	void MoveCamera(float _DeltaTime);


protected:

private:
	float FallenWarriorSpawnTime = 20.0f;
	FVector MapSize;
	
	std::shared_ptr<class ADunkel_Map> Map;
	std::shared_ptr<class ADunkel_Boss> Dunkel;

	UEngineRandom Random;
	UEngineCamera* MainCamera = nullptr;
	
	


};

