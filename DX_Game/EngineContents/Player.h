#pragma once
#include <EngineCore/Pawn.h>
#include "PlayerAnimation.h"



class PlayerLogicValue 
{
public:
	FVector PlayerDir = FVector::LEFT;
	bool IsMoveAbleValue = true;
	bool IsJumpAbleValue = true;

	bool IsGroundValue = false;
	bool IsJumpingValue = true;
	bool IsFallingValue = true;
	bool IsProneValue = false;

	bool IsUsingSkillValue = false;

	int JumpCount = 0;
	int JumpCountMax = 3;

	void PlusJumpCount()
	{
		JumpCount++;
	}
	void StartFalling() {
		IsFallingValue = true;
		IsJumpingValue = false;
	}
	void StartJump() 
	{
		JumpCount = 1;
		IsGroundValue = false;
		IsJumpingValue = true;
		IsFallingValue = false;
	}

	bool IsJumpCountMax()
	{
		return JumpCount >= JumpCountMax;
	}

	void SetGroundTrue()
	{
		IsGroundValue = true;
		IsFallingValue = false;
		IsJumpingValue = false;
		IsMoveAbleValue = true;
		JumpCount = 0;
	}
};



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

	UPlayerAnimation& GetPlayerAnimation()
	{
		return PlayerAnimation;
	}

	std::shared_ptr<class UPlayerFuncManager> GetPlayerFuncManager()
	{
		return PlayerFuncManager;
	}


	std::shared_ptr<class ASkill> GetSkill(std::string_view _SkillName)
	{
		std::string UpperName = UEngineString::ToUpper(_SkillName);
		if (SkillMap.contains(UpperName))
		{
			return SkillMap[UpperName];
		}
		return nullptr;
	}

	void AddSkill(std::string_view _SkillName, std::shared_ptr<class ASkill> _Skill)
	{
		std::string UpperName = UEngineString::ToUpper(_SkillName);
		if (!SkillMap.contains(UpperName))
		{
			SkillMap.insert(std::make_pair(UpperName,_Skill));
		}
	}
	PlayerLogicValue& GetBoolValue()
	{
		return LogicValue;
	}

	void AddJumpPower(float _X, float _Y)
	{
		Velocity.X = _X;
		Velocity.Y += _Y;
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



protected:

private:
	float DeltaTime = 0.0f;
	UPlayerAnimation PlayerAnimation;
	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;
	std::map<std::string, std::shared_ptr<class ASkill>> SkillMap;


	FVector Velocity = FVector::ZERO;
	FVector GravityValue = FVector(0.0f,1960.0f,0.0f);
	FVector GravityAccel = FVector::ZERO;


	
	
	PlayerLogicValue LogicValue;
		
	void CheckKey(float _DeltaTime);
	void InitSkill();

};

