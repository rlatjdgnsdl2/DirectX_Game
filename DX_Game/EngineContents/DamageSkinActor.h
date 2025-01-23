#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class ADamageSkinActor : public AActor
{
public:
	ADamageSkinActor();
	virtual ~ADamageSkinActor();
	ADamageSkinActor(const ADamageSkinActor& _Other) = delete;
	ADamageSkinActor(ADamageSkinActor&& _Other) noexcept = delete;
	ADamageSkinActor& operator=(const ADamageSkinActor& _Other) = delete;
	ADamageSkinActor& operator=(ADamageSkinActor&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;
	void SetDamage(unsigned long long _Damage) 
	{
		if (_Damage > 999999999999) {
			Damage = 999999999999;
		}
		else 
		{ 
			Damage = _Damage;
		}
	};



protected:

private:
	float CurTime = 0.0f;
	unsigned long long Damage = 0;
	
	std::string DamageString;
	std::vector<class DamageSkinRenderer*> SpriteRenderers;
	std::vector<int> DamageNumber;

};

