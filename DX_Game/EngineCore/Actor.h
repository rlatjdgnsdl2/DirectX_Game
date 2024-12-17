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

		//ComponentType* NewPtr = reinterpret_cast<ComponentType*>(ComponentMemory);
		
		std::shared_ptr<ComponentType> NewCom(new(ComponentMemory) ComponentType());

		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			if (nullptr != RootComponent)
			{
				MSGASSERT("���� ���ϱ����� ������ �ʾҽ��ϴ�.");
			}
			RootComponent = NewCom;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{
			ActorComponentList.push_back(NewCom);
		}
		else
		{
			MSGASSERT("���� �ȵ�");
		}

		return NewCom;
	}

	ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	// �������� ����� ����Ǿ����Ƿ� �ʱ�ȭ x, ������ ȣ�� ���� ���� Level�� �ʱ�ȭ��.
	ULevel* World;

	std::shared_ptr<class USceneComponent> RootComponent = nullptr;
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

