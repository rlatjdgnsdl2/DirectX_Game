
#pragma once
#include <EngineBase/Object.h>

// C
// #include <memory.h>
// C++
#include <memory>

// ���� :
class UActorComponent : public UObject
{
	friend class AActor;

public:
	// constrcuter destructer
	ENGINEAPI UActorComponent();
	ENGINEAPI ~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	template<typename ConvertType>
	ConvertType* GetActor()
	{
		return dynamic_cast<ConvertType*>(GetActor());
	}

	ENGINEAPI class AActor* GetActor();
	ENGINEAPI virtual void InitializeComponent() {}
	ENGINEAPI virtual void BeginPlay() {}
	ENGINEAPI virtual void ComponentTick(float _DeltaTime) {};

	ENGINEAPI ULevel* GetWorld();

	ENGINEAPI bool IsActive() override;

	ENGINEAPI bool IsDestroy() override;

protected:

private:
	class AActor* Actor;
};

