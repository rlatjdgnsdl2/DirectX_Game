#include "PreCompile.h"
#include "Player.h"

#include "PhysicsComponent.h"
#include "PlayerFuncManager.h"

void APlayer::Start_Swift_Phantom()
{
	SpriteRenderer->ChangeAnimation("Jump");
	PysicsComponent->SetVelocityY(UContentsPhysicsConst::JumpSpeed);
	PlayerFuncManager->GetFunc(EPlayer_Function::Swift_Phantom)();
}

void APlayer::Update_Swift_Phantom(float _DeltaTime)
{
	if (PysicsComponent->IsGround()) 
	{
		FSM.ChangeState(EPlayer_State::Idle);
		return;
	};
	if (UEngineInput::IsPress(VK_LEFT)) {
		SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	if (UEngineInput::IsPress(VK_RIGHT)) {
		SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
	}

}
