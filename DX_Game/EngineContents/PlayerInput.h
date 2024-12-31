#pragma once




//	Ό³Έν:
class PlayerInput
{
public:
	PlayerInput();
	virtual ~PlayerInput();
	PlayerInput(const PlayerInput& _Other) = delete;
	PlayerInput(PlayerInput&& _Other) noexcept = delete;
	PlayerInput& operator=(const PlayerInput& _Other) = delete;
	PlayerInput& operator=(PlayerInput&& _Other) noexcept = delete;

protected:

private:
	std::map<int, std::function<void()>> KeySetting;

};

