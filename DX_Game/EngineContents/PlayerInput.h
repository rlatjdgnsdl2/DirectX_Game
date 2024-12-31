#pragma once
#include <EngineCore/ActorComponent.h>




//	Ό³Έν:
class PlayerInput :public UActorComponent
{
public:
	PlayerInput();
	virtual ~PlayerInput();
	PlayerInput(const PlayerInput& _Other) = delete;
	PlayerInput(PlayerInput&& _Other) noexcept = delete;
	PlayerInput& operator=(const PlayerInput& _Other) = delete;
	PlayerInput& operator=(PlayerInput&& _Other) noexcept = delete;

	void ComponentTick(float _DeltaTime) override;

protected:

private:
	std::map<int, std::function<void()>> KeySetting;

};

