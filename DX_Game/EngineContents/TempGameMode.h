#pragma once
#include <EngineCore/GameMode.h>
//	Ό³Έν:
class ATempGameMode : public AGameMode
{
public:
	ATempGameMode();
	virtual ~ATempGameMode();
	ATempGameMode(const ATempGameMode& _Other) = delete;
	ATempGameMode(ATempGameMode&& _Other) noexcept = delete;
	ATempGameMode& operator=(const ATempGameMode& _Other) = delete;
	ATempGameMode& operator=(ATempGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;


protected:

private:
	std::shared_ptr<class ATempActor> TempActor;

};

