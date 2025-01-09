#include "PreCompile.h"
#include "PlayerAnimation.h"


UPlayerAnimation::UPlayerAnimation() 
{

}

UPlayerAnimation::~UPlayerAnimation() 
{

}

void UPlayerAnimation::Init()
{
	UAnimationManager::Init();
	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0, 2);
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer->CreateAnimation("Prone", "Player_Prone.png", 0, 0);
	SpriteRenderer->CreateAnimation("UltimateDrive_StartEnd", "Player_UltimateDrive_StartEnd.png", 0, 3);
	SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown", "Player_UltimateDrive_KeyDown.png", 0, 5);
}
