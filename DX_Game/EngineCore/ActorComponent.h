#pragma once
#include <EngineBase/Object.h>


#include <memory>

// ���� :
class UActorComponent : public UObject
{
public:
	// constrcuter destructer
	UActorComponent();
	~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	std::shared_ptr<class AActor> GetActor();

protected:

private:

	// ���Ϳ� ���� �ִ�. ����
	// std::shared_ptr<class AActor> 
	// std::weak_ptr
	class AActor* Actor;
};

