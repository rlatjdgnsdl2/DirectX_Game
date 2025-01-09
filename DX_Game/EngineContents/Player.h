#pragma once
#include <EngineCore/Pawn.h>
#include "PlayerAnimation.h"
#include "PlayerFSM.h"

//	Ό³Έν:
class APlayer : public APawn
{
public:
	APlayer();
	virtual ~APlayer();
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	float GetDeltaTime() const
	{
		return DeltaTime;
	}
	void ChangeAnimation(PAnimation_State _State)
	{
		PlayerAnimation.ChangeState(_State);
	}

	void ChangeState(Player_State _State)
	{
		PlayerFSM.ChangeState(_State);
	}





protected:

private:
	float DeltaTime = 0.0f;
	UPlayerFSM PlayerFSM;
	UPlayerAnimation PlayerAnimation;




	

	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;

	bool IsGround = true;
	bool IsJump = false;


	void Stand(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Prone(float _DeltaTime);
	void Ultimate_Drive(float _DeltaTime);
	
	


	

	




};

