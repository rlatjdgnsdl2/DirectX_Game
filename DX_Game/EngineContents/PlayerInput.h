#pragma once
#include <EngineCore/ActorComponent.h>
#include <EngineBase/EngineDelegate.h>




//	Ό³Έν:
class UPlayerInput :public UActorComponent
{
public:
	UPlayerInput();
	virtual ~UPlayerInput();
	UPlayerInput(const UPlayerInput& _Other) = delete;
	UPlayerInput(UPlayerInput&& _Other) noexcept = delete;
	UPlayerInput& operator=(const UPlayerInput& _Other) = delete;
	UPlayerInput& operator=(UPlayerInput&& _Other) noexcept = delete;

	void ComponentTick(float _DeltaTime) override;


protected:

private:
	std::map<int, EngineDelegate> KeySetting;

};

