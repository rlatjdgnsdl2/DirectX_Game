#pragma once
#include <EngineBase/EngineMath.h>
#include "ActorComponent.h"
#include "TransformObject.h"

// Ό³Έν :
class USceneComponent : public UActorComponent, public UTransformObject
{
	friend class AActor;
public:
	// constrcuter destructer
	ENGINEAPI USceneComponent();
	ENGINEAPI virtual ~USceneComponent() = 0;

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	ENGINEAPI void BeginPlay() override;
	ENGINEAPI void ComponentTick(float _DeltaTime) override;

protected:



private:
};

