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
	class ADunkel_Map* Map;
	FVector MapSize;
	FVector MapPos;

	class ADunkel_Boss* BossDunkel;
	class UDunkel_GUI* Dunkel_GUI;


	UEngineCamera* MainCamera = nullptr;
	
	


};

