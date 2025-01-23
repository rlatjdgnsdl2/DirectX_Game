#include "PreCompile.h"
#include "DamageSkinFactory.h"

#include "DamageSkinActor.h"


DamageSkinFactory::DamageSkinFactory()
{

}

DamageSkinFactory::~DamageSkinFactory()
{

}

void DamageSkinFactory::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	HitDelay -= _DeltaTime;
	if (CurHitCount <= DamageInfo.MaxHitCount) {
		if (HitDelay < 0.0f)
		{
			ADamageSkinActor* DamageSkinActor = GetWorld()->SpawnActor<ADamageSkinActor>().get();
			DamageSkinActor->SetDamage(DamageInfo.Damage+DamageOffset);
			DamageSkinActor->AddActorLocation(FVector(0.0f, OffsetY, 0.0f));
			CurHitCount++;
			HitDelay = DamageInfo.HitDelay;
			DamageOffset += DamageOffset;
			OffsetY += 40.0f;
		}
	}
	else if (CurHitCount > DamageInfo.MaxHitCount)
	{
		Destroy();
	}
}
