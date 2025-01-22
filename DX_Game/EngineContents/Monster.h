#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class AMonster : public AActor
{
public:
	AMonster();
	virtual ~AMonster();
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:
	UFSMStateManager AnimaionFSM;
	class USpriteRenderer* SpriteRenderer;
	class UMyCollision* Collision;
	std::map<std::string, class UCollision*> AttackCollisionMap;
	float HP;
	float Def;
	bool bIsDamagedable;



private:
};

