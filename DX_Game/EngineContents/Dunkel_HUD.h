#pragma once
#include <EngineCore/HUD.h>

//	Ό³Έν:
class ADunkel_HUD :public AHUD
{
public:
	ADunkel_HUD();
	virtual ~ADunkel_HUD();
	ADunkel_HUD(const ADunkel_HUD& _Other) = delete;
	ADunkel_HUD(ADunkel_HUD&& _Other) noexcept = delete;
	ADunkel_HUD& operator=(const ADunkel_HUD& _Other) = delete;
	ADunkel_HUD& operator=(ADunkel_HUD&& _Other) noexcept = delete;

	virtual void BeginPlay() override;

protected:

private:


};

