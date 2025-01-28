#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ASniping : public AActor
{
public:
	// constrcuter destructer
	ASniping();
	virtual ~ASniping();

	// delete Function
	ASniping(const ASniping& _Other) = delete;
	ASniping(ASniping&& _Other) noexcept = delete;
	ASniping& operator=(const ASniping& _Other) = delete;
	ASniping& operator=(ASniping&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	void SetDir(float _Dir) { Dir = _Dir; }

protected:

private:
	float Dir = 1.0f;
	USpriteRenderer* SpriteRenderer;
	UMyCollision* Collision;

};

