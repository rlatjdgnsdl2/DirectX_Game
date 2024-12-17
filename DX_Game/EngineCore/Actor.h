#pragma once
#include "ActorComponent.h"


// ���� :
class AActor : public UObject
{
	friend class ULevel;

public:
	// constrcuter destructer
	ENGINEAPI AActor();
	ENGINEAPI ~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	ENGINEAPI virtual void BeginPlay();
	ENGINEAPI virtual void Tick(float _DeltaTime);

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	template<typename ComponentType>
	inline void CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>, "���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");
		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");
			return nullptr;
		}

		char* ComponentMemory = new char[sizeof(ComponentType)];
		UActorComponent* ComponentPtr = reinterpret_cast<ComponentType*>(ComponentMemory);
		ComponentPtr->Actor = this;

		ComponentType* NewPtr = reinterpret_cast<ComponentType*>(ComponentMemory);
		NewPtr = new(ComponentMemory) ComponentType();
		
		std::shared_ptr<ComponentType> NewComponent(NewPtr);

		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			if (nullptr != RootComponent)
			{
				MSGASSERT("���� ���ϱ����� ������ �ʾҽ��ϴ�.");
			}
			RootComponent = NewComponent;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{
			ActorComponentList.push_back(NewComponent);
		}
		else
		{
			MSGASSERT("���� �ȵ�");
		}

		return NewComponent;
	}

	ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	//������ ȣ�� ���� ���� World�� �ʱ�ȭ�� -> �̸� �ʱ�ȭx.
	ULevel* World;

	std::shared_ptr<class USceneComponent> RootComponent = nullptr;
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

