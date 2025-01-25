#pragma once
#include <EngineCore/Actor.h>


//	Ό³Έν:
class APillarLight :public AActor
{
public:
	APillarLight();
	virtual ~APillarLight();
	APillarLight(const APillarLight& _Other) = delete;
	APillarLight(APillarLight&& _Other) noexcept = delete;
	APillarLight& operator=(const APillarLight& _Other) = delete;
	APillarLight& operator=(APillarLight&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:

private:
	bool bIsCollisionSpawn = false;
	float CollisionSpawnTime = 0.0f;
	class USpriteRenderer* SpriteRenderer;
	class UMyCollision* Collision;

};

