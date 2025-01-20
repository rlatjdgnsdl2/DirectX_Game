#pragma once
#include "PlayerFunction.h"

//	����:
class ARightKey : public APlayerFunction
{
public:
	ARightKey();
	virtual ~ARightKey();
	ARightKey(const ARightKey& _Other) = delete;
	ARightKey(ARightKey&& _Other) noexcept = delete;
	ARightKey& operator=(const ARightKey& _Other) = delete;
	ARightKey& operator=(ARightKey&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;

	virtual void SetActiveTrue() override;
	virtual void SetActiveFalse() override;

protected:

private:

};

