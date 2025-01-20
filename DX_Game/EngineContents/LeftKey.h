#pragma once
#include "PlayerFunction.h"

//	Ό³Έν:
class ALeftKey : public APlayerFunction
{
public:
	ALeftKey();
	virtual ~ALeftKey();
	ALeftKey(const ALeftKey& _Other) = delete;
	ALeftKey(ALeftKey&& _Other) noexcept = delete;
	ALeftKey& operator=(const ALeftKey& _Other) = delete;
	ALeftKey& operator=(ALeftKey&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;
	virtual void SetActiveTrue() override;
	virtual void SetActiveFalse() override;

protected:

private:


};

