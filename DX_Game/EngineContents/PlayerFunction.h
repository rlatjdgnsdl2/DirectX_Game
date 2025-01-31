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
	virtual void SetKey(int _Key)
	{
		Key = _Key;
	}
	virtual int GetKey()
	{
		return Key;
	}

protected:
	class APlayer* Player;
	int Key = -1;
	FPlayerLogic* PlayerLogic;
private:
};

