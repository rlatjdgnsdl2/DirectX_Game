#pragma once
#include "PlayerFunction.h"

//	Ό³Έν:
class ADownKey : public APlayerFunction
{
public:
	ADownKey();
	virtual ~ADownKey();
	ADownKey(const ADownKey& _Other) = delete;
	ADownKey(ADownKey&& _Other) noexcept = delete;
	ADownKey& operator=(const ADownKey& _Other) = delete;
	ADownKey& operator=(ADownKey&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;
	virtual void SetActiveTrue() override;
	virtual void SetActiveFalse() override;

protected:

private:

};

