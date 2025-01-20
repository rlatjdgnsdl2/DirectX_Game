#pragma once
#include <EngineCore/Pawn.h>
#include "Job.h"

//	설명:
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

	void ChangeAnimation(PAnimation_State _State)
	{
		AnimaionFSM.ChangeState(_State);
	}

	std::weak_ptr<class UPlayerFuncManager> GetPlayerFuncManager()
	{
		return PlayerFuncManager;
	}

	FPlayerLogic& GetBoolValue()
	{
		return PlayerLogic;
	}

	void Gravity(float _DeltaTime);

	void MoveUpdate(float _DeltaTime);


	

	void SetVelocityX(float _X)
	{
		Velocity.X = _X;
	}
	void SetVelocityY(float _Y)
	{
		Velocity.Y = _Y;
	}

	void AddVelocityX(float _X)
	{
		Velocity.X += _X;
	}
	void AddVelocityY(float _Y)
	{
		Velocity.Y += _Y;
	}

	void ResetVelocity()
	{
		Velocity = FVector::ZERO;
	}


	std::weak_ptr<class UCollision> GetCollision()
	{
		return Collision;
	}

	void SetGravityAccel(float _Accel)
	{
		GravityAccel = _Accel;
	}

	void SetDownableFloor(bool _Value)
	{
		IsDownableFloor = _Value;
	}

	bool GetDownableFloor()
	{
		return IsDownableFloor;
	}

	std::weak_ptr <class AJob> GetPlayerJob()
	{
		return Job;
	}



protected:

private:
	std::weak_ptr<class USpriteRenderer> SpriteRenderer;
	std::weak_ptr<class UCollision> Collision;
	std::weak_ptr<class AJob> Job;

	//	방향키
	std::map<std::string, std::weak_ptr<class APlayerFunction>> DirFunctionMap;
	//  방향키 제외키
	std::weak_ptr<class UPlayerFuncManager> PlayerFuncManager;

	FPlayerLogic PlayerLogic;


	FVector Velocity = FVector::ZERO;
	bool IsDownableFloor = false;
	float GravityAccel = 0.0f;

		
	void CheckKey(float _DeltaTime);

};

