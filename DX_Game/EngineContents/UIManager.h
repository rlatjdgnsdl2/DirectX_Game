#pragma once
#include <EngineCore/GameMode.h>

//	Ό³Έν:
class UIManager : public AGameMode
{
public:
	UIManager();
	virtual ~UIManager();
	UIManager(const UIManager& _Other) = delete;
	UIManager(UIManager&& _Other) noexcept = delete;
	UIManager& operator=(const UIManager& _Other) = delete;
	UIManager& operator=(UIManager&& _Other) noexcept = delete;
	


protected:

private:
	

};

