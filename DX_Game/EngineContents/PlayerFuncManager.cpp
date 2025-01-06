#include "PreCompile.h"
#include "PlayerFuncManager.h"
#include "Player.h"



UPlayerFuncManager::UPlayerFuncManager()
{
	Player = dynamic_cast<APlayer*>(GetActor());
	{
		UPlayerFunc NewFunc;
		NewFunc.AddDownEvent([this]()
			{
				Player->GetSprtieRenderer()->ChangeAnimation("Walk");
				Player->SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
			});
		NewFunc.AddPressEvent([this]()
			{
				APlayer* Player = dynamic_cast<APlayer*>(GetActor());
				Player->AddRelativeLocation(FVector(-100.0f * Player->GetDeltaTime(), 0.0f, 0.0f));
			});
		SetFunc("Walk_Left", NewFunc);
	}

	{
		UPlayerFunc NewFunc;
		NewFunc.AddDownEvent([this]()
			{
				Player->GetSprtieRenderer()->ChangeAnimation("Walk");
				Player->SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
			});
		NewFunc.AddPressEvent([this]()
			{
				APlayer* Player = dynamic_cast<APlayer*>(GetActor());
				Player->AddRelativeLocation(FVector(100.0f * Player->GetDeltaTime(), 0.0f, 0.0f));
			});
		SetFunc("Walk_Right", NewFunc);
	}








}

UPlayerFuncManager::~UPlayerFuncManager()
{

}
