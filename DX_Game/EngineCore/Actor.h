#pragma once
#include "ActorComponent.h"


// 설명 :
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
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>, "액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");
		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");
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
				MSGASSERT("아직 RootComponent를 만들지 않았습니다.");
			}
			RootComponent = NewComponent;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{
			ActorComponentList.push_back(NewComponent);
		}
		else
		{
			MSGASSERT("");
		}

		return NewComponent;
	}

	ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	//생성자 호출 전에 먼저 World가 초기화됨 -> 미리 초기화x.
	ULevel* World;

	std::shared_ptr<class USceneComponent> RootComponent = nullptr;
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

