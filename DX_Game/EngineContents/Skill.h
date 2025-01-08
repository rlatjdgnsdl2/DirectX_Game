#pragma once
#include <EngineCore/Actor.h>



//	Ό³Έν:
class ASkill : public AActor
{
public:
	ASkill();
	virtual ~ASkill();
	ASkill(const ASkill& _Other) = delete;
	ASkill(ASkill&& _Other) noexcept = delete;
	ASkill& operator=(const ASkill& _Other) = delete;
	ASkill& operator=(ASkill&& _Other) noexcept = delete;


protected:
	AActor* Owner = nullptr;
	std::map<int, std::shared_ptr<class USpriteRenderer>> SpriteRenderers;
	std::map<int, std::shared_ptr<class UCollision>> Collisions;
	
private:

};

