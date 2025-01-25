#include "PreCompile.h"
#include "CQ57.h"

ACQ57::ACQ57()
{

	SpriteRenderer->CreateAnimation("Spawn", "Elite_Spawn", 0, 7, 1.0f / 8, false);
	SpriteRenderer->CreateAnimation("KnockBack", "CQ57_KnockBack", 0, 26, 2.0f / 27, false);
	SpriteRenderer->CreateAnimation("PhantomBlow", "CQ57_PhantomBlow", 0, 13, 2.0f / 14, false);

	FSM.CreateState(0, 
		[this](float _DeltaTime) 
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				FSM.ChangeState(1);
			}
		},
		[this]() 
		{
			SpriteRenderer->ChangeAnimation("Spawn", true);
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 0.0f, UContentsConst::MONSTER_ZPOS));
		});

	
}

ACQ57::~ACQ57()
{
}

