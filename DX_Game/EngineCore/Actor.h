#pragma once
#include "ActorComponent.h"


// ���ϱ����� �̾߱��� ���ô�.
// ���� :
// �𸮾󿡼� Actor�� ���� Ʈ�������� ������ �ʴ´�.
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


	// �̳༮ �� ���� 
	template<typename ComponentType>
	void CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>, "���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");
			return nullptr;
			// static_assert
		}

		char* ComMemory = new char[sizeof(ComponentType)];

		UActorComponent* ComPtr = reinterpret_cast<ComponentType*>(ComMemory);
		ComPtr->Actor = this;

		ComponentType* NewPtr = reinterpret_cast<ComponentType*>(ComMemory);
		// �������� �����ϰ�
		// �÷��̽���Ʈ new 
		std::shared_ptr<ComponentType> NewCom(new(ComMemory) ComponentType());

		// ���� �׳� ActorComponent
		// ���� �׳� SceneComponent



		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			// ���ϱ����� ���ԵǾ�� �Ѵ�.
			if (nullptr != RootComponent)
			{
				MSGASSERT("���� ���ϱ����� ������ �ʾҽ��ϴ�.");
			}

			RootComponent = NewCom;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{

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
	// �ʱ�ȭ �ϸ� �ȵ˴ϴ�.
	// �������� ����� ����Ǿ����ϱ�.
	ULevel* World;

	std::shared_ptr<class USceneComponent> RootComponent = nullptr;

	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

