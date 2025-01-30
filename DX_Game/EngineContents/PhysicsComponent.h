#pragma once
#include <EngineCore/SceneComponent.h>

// Ό³Έν :
class UPhysicComponent : public USceneComponent
{
public:
	// constrcuter destructer
	UPhysicComponent();
	virtual ~UPhysicComponent();

	// delete Function
	UPhysicComponent(const UPhysicComponent& _Other) = delete;
	UPhysicComponent(UPhysicComponent&& _Other) noexcept = delete;
	UPhysicComponent& operator=(const UPhysicComponent& _Other) = delete;
	UPhysicComponent& operator=(UPhysicComponent&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void ComponentTick(float _DeltaTime) override;

	void GravityTrue() { bIsGravity = true; }
	void GravityFalse() { bIsGravity = false; }
	void SwitchGravity() { bIsGravity = !bIsGravity; }
	bool IsGravity() { return bIsGravity; }

	void SetVelocity(FVector _Velocity) { Velocity = _Velocity; }
	void AddVelocity(FVector _Velocity) { Velocity += _Velocity; }

protected:

private:
	FVector Velocity = FVector(0.0f, 0.0f, 0.0f);

	void Gravity(class AActor* _Actor, float _DeltaTimte);
	void Move(class AActor* _Actor, float _DeltaTimte);


	bool bIsGravity = false;

};

