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

	virtual void SetOwner(std::shared_ptr<class AActor> _Owner)
	{
		Owner = _Owner;
	}
	void SetKey(int _Key)
	{
		Key = _Key;
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
	std::weak_ptr<AActor> Owner;
	int Key = -1;
private:

};

