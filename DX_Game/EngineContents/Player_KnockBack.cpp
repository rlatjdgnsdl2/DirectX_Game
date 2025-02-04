#include "PreCompile.h"
#include "Player.h"


void APlayer::Start_KnockBack() 
{
	GetGameInstance<MyGameInstance>()->PlayerStatus.KnockBackTime = 2.0f;
	SpriteRenderer->ChangeAnimation("Stand");
}
void APlayer::Update_KnockBack(float _DeltaTime) 
{
	if (!GetGameInstance<MyGameInstance>()->PlayerStatus.IsKnockBack(_DeltaTime)) 
	{
		ChangeState(EPlayer_State::Idle);
	};
}