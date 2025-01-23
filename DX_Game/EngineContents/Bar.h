#pragma once
#include <EngineCore/ImageWidget.h>

//	Ό³Έν:
class UBar: public UImageWidget
{
public:
	UBar();
	virtual ~UBar();
	UBar(const UBar& _Other) = delete;
	UBar(UBar&& _Other) noexcept = delete;
	UBar& operator=(const UBar& _Other) = delete;
	UBar& operator=(UBar&& _Other) noexcept = delete;

	virtual void BarLerp(float _StartPercent, float _EndPercent, float _DeltaTime ,bool& _bIsChange);

protected:
	float CurTime = 0.0f;
	float StartPercent;
	float TargetPercent;
private:


};

