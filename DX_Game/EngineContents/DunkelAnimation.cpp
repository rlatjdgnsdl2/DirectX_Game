#include "PreCompile.h"
#include "DunkelAnimation.h"


UDunkelAnimation::UDunkelAnimation() 
{

}

UDunkelAnimation::~UDunkelAnimation() 
{

}

void UDunkelAnimation::Init()
{
	UAnimationManager::Init();
	SpriteRenderer->CreateAnimation("Stand", "Dunkel_Stand", 0, 12);
	SpriteRenderer->CreateAnimation("Spanw", "Dunkel_Spawn", 0, 31 );
	

	CreateState(DunkelAnim_State::Spawn,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Spawn");
		});
	CreateState(DunkelAnim_State::Stand,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Stand");
		});
	ChangeState(DunkelAnim_State::Spawn);


}

