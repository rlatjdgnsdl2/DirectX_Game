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

	void ChangeState(Skill_Frame _Frame)
	{
		FrameState.ChangeState(_Frame);
	};


protected:
	AActor* Owner = nullptr;
	UFSMStateManager FrameState;
	std::map<std::string_view, std::shared_ptr<class USpriteRenderer>> SpriteRenderers;
	std::shared_ptr<class UCollision> Collisions;
	
private:

};

