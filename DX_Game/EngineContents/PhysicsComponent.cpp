#include "PreCompile.h"
#include "PhysicsComponent.h"
#include "ContentsPhysics.h"

UPhysicsComponent::UPhysicsComponent()
{
}

UPhysicsComponent::~UPhysicsComponent()
{
}

void UPhysicsComponent::BeginPlay()
{
	UActorComponent::BeginPlay();
}

void UPhysicsComponent::ComponentTick(float _DeltaTime)
{
	UActorComponent::ComponentTick(_DeltaTime);
	if (nullptr == GetActor())
	{
		return;
	}

	if (!bIsGround)
	{
		Gravity(_DeltaTime);
	}
	UpdateVelocity(_DeltaTime);
}

void UPhysicsComponent::Gravity(float _DeltaTime)
{
	Velocity.Y = UContentsPysics::ApplyGravity(Velocity.Y, _DeltaTime);
	if (Velocity.Y < 0.0f)
	{
		bIsFalling = true;
		bIsJumping = false;
	}
	else if (Velocity.Y > 0.0f)
	{
		bIsFalling = false;
		bIsJumping = true;
	}
}

void UPhysicsComponent::UpdateVelocity(float _DeltaTimte)
{
	GetActor()->AddActorLocation(Velocity * _DeltaTimte);
}






