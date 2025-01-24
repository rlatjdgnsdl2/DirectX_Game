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

	void SetDamage(float _Damage) {
		if (bIsDamagedable) {
			HP -= _Damage;
			if (HP <= 0.0f)
			{
				HP = 0.0f;
			}
		}
	}
	bool IsDamagedable() {
		return bIsDamagedable;
	}

	void InsertCollision(std::string _Name, class UMyCollision* _Collision) {
		std::string UpperName = UEngineString::ToUpper(_Name);
		CollisionMap.insert(std::make_pair(UpperName, _Collision));
	}
	UMyCollision* GetCollision(std::string _Name) {
		std::string UpperName = UEngineString::ToUpper(_Name);
		return CollisionMap[UpperName];
	}

protected:
	UFSMStateManager AnimaionFSM;
	class USpriteRenderer* SpriteRenderer;
	std::map<std::string, class UMyCollision*> CollisionMap;

	float HP = 0.0f;
	bool bIsDamagedable = true;
	bool bIsAttack = false;

	int Dir = 1;

	virtual void StartSpawn() {}
	virtual void UpdateSpawn(float _DeltaTime) {}

	virtual void StartStand() {}
	virtual void UpdateStand(float _DeltaTime) {}

	virtual void StartMove() {}
	virtual void UpdateMove(float _DeltaTime) {}

	virtual void StartAttack() {}
	virtual void UpdateAttack(float _DeltaTime) {}

	virtual void StartDie() {}
	virtual void UpdateDie(float _DeltaTime) {}
private:





};

