#pragma once
#include <EngineCore/ImageWidget.h>

//	Ό³Έν:
class UPlayerHpBar :public UImageWidget
{
public:
	UPlayerHpBar();
	virtual ~UPlayerHpBar();
	UPlayerHpBar(const UPlayerHpBar& _Other) = delete;
	UPlayerHpBar(UPlayerHpBar&& _Other) noexcept = delete;
	UPlayerHpBar& operator=(const UPlayerHpBar& _Other) = delete;
	UPlayerHpBar& operator=(UPlayerHpBar&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;

	virtual void HpBarLerp(float _StartPercent, float _EndPercent, float _DeltaTime);

protected:

private:
	bool bIsHpChange = false;
	float CurTime =0.0f;
	float StartHpPercent;
	float TargetHpPercent;

};

