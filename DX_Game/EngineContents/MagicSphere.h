#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class AMagicSphere : public AActor
{
public:
	// constrcuter destructer
	AMagicSphere();
	virtual ~AMagicSphere();

	// delete Function
	AMagicSphere(const AMagicSphere& _Other) = delete;
	AMagicSphere(AMagicSphere&& _Other) noexcept = delete;
	AMagicSphere& operator=(const AMagicSphere& _Other) = delete;
	AMagicSphere& operator=(AMagicSphere&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	void SetDir(float _Dir) { Dir = _Dir; }

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	class UMyCollision* Collision = nullptr;
	float Dir = 1.0f;
	int PrevIndex = 0;
	int CurIndex = 0;

	float DamageDelay = 0.5f;



};

