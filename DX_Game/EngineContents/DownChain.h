#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ADownChain : public AActor
{
public:
	// constrcuter destructer
	ADownChain();
	virtual ~ADownChain();

	// delete Function
	ADownChain(const ADownChain& _Other) = delete;
	ADownChain(ADownChain&& _Other) noexcept = delete;
	ADownChain& operator=(const ADownChain& _Other) = delete;
	ADownChain& operator=(ADownChain&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:

private:
	class USpriteRenderer* SpriteRenderer;
	std::vector<class UMyCollision*> Collisions;

	int PrevIndex =0;
	int CurIndex =0;

};

