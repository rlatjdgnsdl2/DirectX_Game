#pragma once
#include <EngineCore/SpriteRenderer.h>
//	Ό³Έν:
class DamageSkinRenderer : public USpriteRenderer
{
public:
	DamageSkinRenderer();
	virtual ~DamageSkinRenderer();
	DamageSkinRenderer(const DamageSkinRenderer& _Other) = delete;
	DamageSkinRenderer(DamageSkinRenderer&& _Other) noexcept = delete;
	DamageSkinRenderer& operator=(const DamageSkinRenderer& _Other) = delete;
	DamageSkinRenderer& operator=(DamageSkinRenderer&& _Other) noexcept = delete;

	void ComponentTick(float _DeltaTime) override;
	float GetAlpha() const
	{
		return Alpha;
	}

protected:

private:
	float Alpha = 1.0f;
	float ContinueTime = 1.0f;

};

