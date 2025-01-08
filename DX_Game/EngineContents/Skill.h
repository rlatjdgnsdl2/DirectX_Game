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

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	void SetOwner(AActor* _Owner) { Owner = _Owner; }


protected:
	AActor* Owner = nullptr;
	

	std::map<std::string_view, std::shared_ptr<class USpriteRenderer>> SpriteRenderers;
	std::map<int, std::shared_ptr<class UCollision>> Collisions;
	
private:

};

