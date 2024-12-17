#pragma once
#include <EngineBase/Object.h>


// Ό³Έν :
class UActorComponent : public UObject
{
	friend class AActor;
public:
	// constrcuter destructer
	ENGINEAPI UActorComponent();
	ENGINEAPI virtual ~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	class AActor* GetActor() {
		return Actor;
	}

	ENGINEAPI virtual void InitializeComponent() {}
	ENGINEAPI virtual void BeginPlay() {}
protected:
private:

	class AActor* Actor;
};

