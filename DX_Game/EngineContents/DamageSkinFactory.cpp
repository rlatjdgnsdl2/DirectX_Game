#include "PreCompile.h"
#include "DamageSkinFactory.h"

#include "DamageSkinActor.h"


ADamageSkinFactory::ADamageSkinFactory()
{

}

ADamageSkinFactory::~ADamageSkinFactory()
{

}

void ADamageSkinFactory::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	HitDelay -= _DeltaTime;
	if (CurHitCount <= DamageInfo.MaxHitCount) {
		if (HitDelay < 0.0f)
		{
			ADamageSkinActor* DamageSkinActor = GetWorld()->SpawnActor<ADamageSkinActor>().get();
			DamageSkinActor->SetDamage(DamageInfo.Damage);
			DamageSkinActor->SetActorLocation(FVector(SpawnLocation.X, SpawnLocation.Y+OffsetY, 0.0f));
			CurHitCount++;
			HitDelay = DamageInfo.HitDelay;
			OffsetY += 40.0f;
		}
	}
	else if (CurHitCount > DamageInfo.MaxHitCount)
	{
		Destroy();
	}
}
