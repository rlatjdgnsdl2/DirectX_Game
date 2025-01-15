#pragma once
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


protected:

private:
	std::shared_ptr<class ADunkel_Map> Map;
	std::shared_ptr<class ADunkel_Boss> Dunkel;


};

