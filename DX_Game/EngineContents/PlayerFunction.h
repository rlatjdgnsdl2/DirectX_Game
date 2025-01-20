#pragma once
#include "ActorFunction.h"

//	Ό³Έν:
class APlayerFunction : public AActorFunction
{
public:
	APlayerFunction();
	virtual ~APlayerFunction();
	APlayerFunction(const APlayerFunction& _Other) = delete;
	APlayerFunction(APlayerFunction&& _Other) noexcept = delete;
	APlayerFunction& operator=(const APlayerFunction& _Other) = delete;
	APlayerFunction& operator=(APlayerFunction&& _Other) noexcept = delete;

	virtual void SetOwner(class AActor* _Owner) override;

protected:
	class APlayer* Player;
private:
};

