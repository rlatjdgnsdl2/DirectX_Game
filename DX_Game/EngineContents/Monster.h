#pragma once
#include <EngineCore/Actor.h>

//	����:
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
		if (CollisionMap.find(UpperName) != CollisionMap.end())
		{
			MSGASSERT("�̹� �����ϴ� �ݸ����Դϴ�.");
			return;
		}
		CollisionMap.insert(std::make_pair(UpperName, _Collision));
	}
	UMyCollision* GetCollision(std::string _Name) {
		std::string UpperName = UEngineString::ToUpper(_Name);
		if (CollisionMap.find(UpperName) == CollisionMap.end())
		{
			MSGASSERT("�������� �ʴ� �ݸ����Դϴ�.");
			return nullptr;
		}
		return CollisionMap[UpperName];
	}

protected:
	UFSMStateManager FSM;
	class USpriteRenderer* SpriteRenderer;
	std::map<std::string, class UMyCollision*> CollisionMap;

	double HP = 0.0;
	bool bIsDamagedable = true;
	bool bIsAttacking = false;
	float Dir = 1.0f;

	virtual void StartSpawn() {}
	virtual void UpdateSpawn(float _DeltaTime) {}

	virtual void StartStand() {}
	virtual void UpdateStand(float _DeltaTime) {}

	virtual void StartMove() {}
	virtual void UpdateMove(float _DeltaTime) {}
	
	virtual void StartDie() {}
	virtual void UpdateDie(float _DeltaTime) {}

	virtual void StartAttack() {}
	virtual void UpdateAttack(float _DeltaTime) {}
private:





};

