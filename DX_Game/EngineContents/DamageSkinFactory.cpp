#include "PreCompile.h"
#include "DamageSkinFactory.h"

#include "DamageSkinActor.h"
#include "MyCollision.h"
#include "Monster.h"


ADamageSkinFactory::ADamageSkinFactory()
{

}

ADamageSkinFactory::~ADamageSkinFactory()
{

}

void ADamageSkinFactory::SetSpawnLocation()
{	
	if (MonsterColl == nullptr)
	{
		return;
	}
	FVector ActorLocation = MonsterColl->GetActor()->GetActorLocation();
	FVector CollSize = FVector(0.0f, std::abs(MonsterColl->GetWorldScale3D().Y));
	SpawnLocation = ActorLocation + CollSize;
}

void ADamageSkinFactory::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (MonsterColl->GetActor()->IsDestroy())
	{
		Destroy();
		return;
	}
	bool IsDamageable = dynamic_cast<AMonster*>(MonsterColl->GetActor())->IsDamagedable();
	if (!IsDamageable)
	{
		DamageInfo.Damage = 0.0f;
	}

	if (CurCycle < DamageInfo.MaxHitCycle)
	{

		if (CurHitCount <= DamageInfo.MaxHitCount) {
			HitDelay -= _DeltaTime;
			if (HitDelay < 0.0f)
			{
				ADamageSkinActor* DamageSkinActor = GetWorld()->SpawnActor<ADamageSkinActor>().get();
				int Damage = Random.RandomInt(DamageInfo.Damage - DamageInfo.Damage / 10, DamageInfo.Damage + DamageInfo.Damage / 10);
				DamageSkinActor->SetDamage(Damage);
				if (nullptr != MonsterColl->GetActor())
				{
					dynamic_cast<AMonster*>(MonsterColl->GetActor())->SetDamage(Damage);
				}
				FVector NewSpawnLocation = FVector(SpawnLocation.X, SpawnLocation.Y + OffsetY, 0.0f);
				DamageSkinActor->SetActorLocation(NewSpawnLocation);
				CurHitCount++;
				HitDelay = DamageInfo.HitDelay;
				OffsetY += 40.0f;
			}
		}
		else if (CurHitCount > DamageInfo.MaxHitCount)
		{
			CurCycle++;
			CurHitCount = 0;
			HitDelay = DamageInfo.HitDelay;
			OffsetY = 0.0f;
		}

	}
	else
	{
		Destroy();
	}
}
