#include "PreCompile.h"
#include "PhysicsComponent.h"

UPhysicComponent::UPhysicComponent()
{
}

UPhysicComponent::~UPhysicComponent()
{
}

void UPhysicComponent::BeginPlay()
{
	USceneComponent::BeginPlay();
}

void UPhysicComponent::ComponentTick(float _DeltaTime)
{
	USceneComponent::ComponentTick(_DeltaTime);
	AActor* Actor = GetActor();
	if (nullptr == Actor)
	{
		return;
	}
	if (true)
	{
		Gravity(Actor, _DeltaTime);
	}
}

void UPhysicComponent::Gravity(AActor* _Actor, float _DeltaTimte)
{
	AActor* Actor = _Actor;
	Actor->AddActorLocation(FVector(0.0f, Velocity.Y* _DeltaTimte, 0.0f));
}

void UPhysicComponent::Move(AActor* _Actor, float _DeltaTimte)
{
	AActor* Actor = _Actor;
	Actor->AddActorLocation(FVector(Velocity.X* _DeltaTimte, 0.0f, 0.0f));
}

