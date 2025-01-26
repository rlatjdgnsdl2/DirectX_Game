#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AShot : public AActor
{
public:
	// constrcuter destructer
	AShot();
	virtual ~AShot();

	// delete Function
	AShot(const AShot& _Other) = delete;
	AShot(AShot&& _Other) noexcept = delete;
	AShot& operator=(const AShot& _Other) = delete;
	AShot& operator=(AShot&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:

private:
	int PrevIndex = 0;
	int CurIndex = 0;
	class USpriteRenderer* SpriteRenderer;
	class UMyCollision* Collision;

};

