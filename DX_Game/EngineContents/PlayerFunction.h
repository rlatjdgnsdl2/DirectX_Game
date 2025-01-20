#pragma once
#include "ActorFunction.h"

//	����:
class APlayerFunction : public AActorFunction
{
public:
	APlayerFunction();
	virtual ~APlayerFunction();
	APlayerFunction(const APlayerFunction& _Other) = delete;
	APlayerFunction(APlayerFunction&& _Other) noexcept = delete;
	APlayerFunction& operator=(const APlayerFunction& _Other) = delete;
	APlayerFunction& operator=(APlayerFunction&& _Other) noexcept = delete;

	virtual void SetOwner(std::shared_ptr<class AActor> _Owner) override;

protected:
	std::weak_ptr<class APlayer> Player;
private:
};

