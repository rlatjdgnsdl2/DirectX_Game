#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class AActorFunction : public AActor
{
public:
	AActorFunction();
	virtual ~AActorFunction();
	AActorFunction(const AActorFunction& _Other) = delete;
	AActorFunction(AActorFunction&& _Other) noexcept = delete;
	AActorFunction& operator=(const AActorFunction& _Other) = delete;
	AActorFunction& operator=(AActorFunction&& _Other) noexcept = delete;

	virtual void BeginPlay() override;

	virtual void SetOwner(AActor* _Owner)
	{
		Owner = _Owner;
	}
	virtual void SetActiveTrue()
	{
		SetActive(true);
	}
	virtual void SetActiveFalse()
	{
		SetActive(false);
	}


protected:
	AActor* Owner;
	
private:

};

