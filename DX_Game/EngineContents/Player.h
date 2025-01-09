#pragma once
#include <EngineCore/Pawn.h>
#include "PlayerAnimation.h"

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
	void ChanegeAnimation(std::string_view _AnimationName)
	{
		PlayerAnimation.ChangeAnimation(_AnimationName);
	}


protected:

private:
	float DeltaTime = 0.0f;
	UPlayerAnimation PlayerAnimation;



	

	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;



	bool IsGround = true;
	bool IsJump = false;


	void KeyCheck();
	


	

	




};

