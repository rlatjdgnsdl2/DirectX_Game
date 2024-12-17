#pragma once
#include <EngineCore/GameMode.h>
//	Ό³Έν:
class TempGameMode : public AGameMode
{
public:
	TempGameMode();
	virtual ~TempGameMode();
	TempGameMode(const TempGameMode& _Other) = delete;
	TempGameMode(TempGameMode&& _Other) noexcept = delete;
	TempGameMode& operator=(const TempGameMode& _Other) = delete;
	TempGameMode& operator=(TempGameMode&& _Other) noexcept = delete;

protected:

private:

};

