#pragma once
#include <EngineCore/ActorComponent.h>

// ���� :
class UPhysicsComponent : public UActorComponent
{
public:
	// constrcuter destructer
	UPhysicsComponent();
	virtual ~UPhysicsComponent();

	// delete Function
	UPhysicsComponent(const UPhysicsComponent& _Other) = delete;
	UPhysicsComponent(UPhysicsComponent&& _Other) noexcept = delete;
	UPhysicsComponent& operator=(const UPhysicsComponent& _Other) = delete;
	UPhysicsComponent& operator=(UPhysicsComponent&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void ComponentTick(float _DeltaTime) override;

	void SetVelocity(FVector _Velocity) { Velocity = _Velocity; }
	void SetVelocityX(float _X) { Velocity.X = _X; }
	void SetVelocityY(float _Y) { Velocity.Y = _Y; }

	void AddVelocity(FVector _Velocity) { Velocity += _Velocity; }
	void AddVelocityX(float _X) { Velocity.X += _X; }
	void AddVelocityY(float _Y) { Velocity.Y += _Y; }

	
	bool IsGround() { return bIsGround; }
	bool IsJumping() { return bIsJumping; }
	bool IsFalling() { return bIsFalling; }

	void SetGroundTrue() { bIsGround = true; }
	void SetGroundFalse() { bIsGround = false; }

	

protected:

private:
	FVector Velocity = FVector(0.0f, 0.0f, 0.0f);

	bool bIsGround = true;
	bool bIsJumping = false;
	bool bIsFalling = false;

	void Gravity(float _DeltaTimte);
	void UpdateVelocity(float _DeltaTimte);





};

