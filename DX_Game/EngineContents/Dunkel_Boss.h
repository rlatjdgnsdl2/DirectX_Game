#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class ADunkel_Boss :public AActor
{
public:
	ADunkel_Boss();
	virtual ~ADunkel_Boss();
	ADunkel_Boss(const ADunkel_Boss& _Other) = delete;
	ADunkel_Boss(ADunkel_Boss&& _Other) noexcept = delete;
	ADunkel_Boss& operator=(const ADunkel_Boss& _Other) = delete;
	ADunkel_Boss& operator=(ADunkel_Boss&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:

private:
	float CurTime = 0.0f;

	UFSMStateManager AnimaionFSM;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
	std::shared_ptr<class UCollision> Collision;


	std::map<std::string, std::shared_ptr<class UCollision>> AttackCollisionMap;


};

