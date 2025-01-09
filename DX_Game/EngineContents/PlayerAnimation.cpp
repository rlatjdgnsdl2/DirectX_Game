#include "PreCompile.h"
#include "PlayerAnimation.h"


UPlayerAnimation::UPlayerAnimation()
{
	AnimationNode[PAnimation_State::Stand] = { PAnimation_State::Stand, PAnimation_State::Walk, PAnimation_State::Jump, PAnimation_State::Prone, PAnimation_State::Ultimate_Drive };
	AnimationNode[PAnimation_State::Walk] = { PAnimation_State::Stand, PAnimation_State::Walk,PAnimation_State::Jump, PAnimation_State::Prone, PAnimation_State::Ultimate_Drive };
	AnimationNode[PAnimation_State::Jump] = { PAnimation_State::Jump };
	AnimationNode[PAnimation_State::Prone] = { PAnimation_State::Stand, PAnimation_State::Walk, PAnimation_State::Jump, PAnimation_State::Prone, PAnimation_State::Ultimate_Drive };
	AnimationNode[PAnimation_State::Ultimate_Drive] = { PAnimation_State::Ultimate_Drive, PAnimation_State::Stand, PAnimation_State::Walk, PAnimation_State::Prone, PAnimation_State::Ultimate_Drive };
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

bool UPlayerAnimation::CheckAnimNode(PAnimation_State _CurAnimState,PAnimation_State _NextAnimState)
{
	if (AnimationNode.contains(_CurAnimState))
	{
		for (auto& AnimState : AnimationNode[_CurAnimState])
		{
			if (AnimState == _NextAnimState)
			{
				return true;
			}
		}
	}
	return false;
}
