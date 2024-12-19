#pragma once
#include <EngineBase/Object.h>

// C
// #include <memory.h>
// C++
#include <memory>

// ���� :
class UActorComponent : public UObject
{
	friend AActor;

public:
	// constrcuter destructer
	UActorComponent();
	~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	class AActor* GetActor();
	ENGINEAPI virtual void InitializeComponent() {}
	ENGINEAPI virtual void BeginPlay() {}

protected:

private:

	// ���Ϳ� ���� �ִ�. ����
	// std::shared_ptr<class AActor> 
	// std::weak_ptr
	class AActor* Actor;
};

