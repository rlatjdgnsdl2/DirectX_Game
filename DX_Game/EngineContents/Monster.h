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
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
	std::shared_ptr<class UCollision> Collision;
	std::map<std::string, std::shared_ptr<class UCollision>> AttackCollisionMap;
private:
};

