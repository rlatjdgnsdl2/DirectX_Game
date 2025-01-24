#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class ADunkel_Meteo : public AActor
{
public:
	ADunkel_Meteo();
	virtual ~ADunkel_Meteo();
	ADunkel_Meteo(const ADunkel_Meteo& _Other) = delete;
	ADunkel_Meteo(ADunkel_Meteo&& _Other) noexcept = delete;
	ADunkel_Meteo& operator=(const ADunkel_Meteo& _Other) = delete;
	ADunkel_Meteo& operator=(ADunkel_Meteo&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;
	
	void SetDir(float _Dir) { Dir = _Dir; }
	void SetStartPos(FVector _Pos) { StartPos = _Pos; }



protected:

private:
	class USpriteRenderer* SpriteRenderer;
	class UMyCollision* Collision;
	FVector StartPos = FVector::ZERO;
	float Dir =1;
	UFSMStateManager AnimaionFSM;

};

