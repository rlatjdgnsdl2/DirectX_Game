#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AUpChain : public AActor
{
public:
	// constrcuter destructer
	AUpChain();
	virtual ~AUpChain();

	// delete Function
	AUpChain(const AUpChain& _Other) = delete;
	AUpChain(AUpChain&& _Other) noexcept = delete;
	AUpChain& operator=(const AUpChain& _Other) = delete;
	AUpChain& operator=(AUpChain&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	class UMyCollision* Collision = nullptr;
	int PrevIndex = 0;
	int CurIndex = 0;
};

