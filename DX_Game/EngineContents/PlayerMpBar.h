#pragma once
#include "Bar.h"

//	����:
class UPlayerMpBar : public UBar
{
public:
	UPlayerMpBar();
	virtual ~UPlayerMpBar();
	UPlayerMpBar(const UPlayerMpBar& _Other) = delete;
	UPlayerMpBar(UPlayerMpBar&& _Other) noexcept = delete;
	UPlayerMpBar& operator=(const UPlayerMpBar& _Other) = delete;
	UPlayerMpBar& operator=(UPlayerMpBar&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
	void SetPlayerMpBarEffect(class UPlayerMpBarEffect* _PlayerMpBarEffect) { PlayerMpBarEffect = _PlayerMpBarEffect; }


protected:

private:
	class UPlayerMpBarEffect* PlayerMpBarEffect;
	bool bIsPlayEffect = false;
	
};

