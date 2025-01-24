#pragma once
#include "Bar.h"

//	Ό³Έν:
class UPlayerHpBar :public UBar
{
public:
	UPlayerHpBar();
	virtual ~UPlayerHpBar();
	UPlayerHpBar(const UPlayerHpBar& _Other) = delete;
	UPlayerHpBar(UPlayerHpBar&& _Other) noexcept = delete;
	UPlayerHpBar& operator=(const UPlayerHpBar& _Other) = delete;
	UPlayerHpBar& operator=(UPlayerHpBar&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
	void SetPlayerHpBarEffect(class UPlayerHpBarEffect* _PlayerHpBarEffect) { PlayerHpBarEffect = _PlayerHpBarEffect; }
	

protected:

private:
	bool bIsPlayEffect = false;
	class UPlayerHpBarEffect* PlayerHpBarEffect;
	
	

};

