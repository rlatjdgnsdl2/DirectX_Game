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
	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0, 2,1.0f/3);
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3, 1.0f / 4);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer->CreateAnimation("Prone", "Player_Prone.png", 0, 0);

	SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown", "Player_UltimateDrive_KeyDown.png", 0, 5);

	CreateState(PAnimation_State::Stand,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Stand");
		});

	CreateState(PAnimation_State::Walk,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Walk");
		});

	CreateState(PAnimation_State::Jump,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Jump");
		});

	CreateState(PAnimation_State::Prone,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Prone");
		});

	CreateState(PAnimation_State::Ultimate_Drive,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("UltimateDrive_KeyDown");
		});
}


