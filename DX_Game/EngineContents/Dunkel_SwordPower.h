#pragma once
#include <EngineCore/Actor.h>
//	Ό³Έν:
class ADunkel_SwordPower : public AActor
{
public:
	ADunkel_SwordPower();
	virtual ~ADunkel_SwordPower();
	ADunkel_SwordPower(const ADunkel_SwordPower& _Other) = delete;
	ADunkel_SwordPower(ADunkel_SwordPower&& _Other) noexcept = delete;
	ADunkel_SwordPower& operator=(const ADunkel_SwordPower& _Other) = delete;
	ADunkel_SwordPower& operator=(ADunkel_SwordPower&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SetDir(float _Dir) { Dir = _Dir; }
	void SetStartPos(FVector _Pos) { StartPos = _Pos; }


protected:

private:
	class USpriteRenderer* SpriteRenderer;
	class UMyCollision* Collision;

	float Dir = 1;
	float SpawnTime = 0.0f;

	FVector StartPos = FVector::ZERO;
	

};

