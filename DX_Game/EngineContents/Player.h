#pragma once
#include <EngineCore/Pawn.h>




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
		IsJumpAbleValue = true;
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

	


	void ChangeAnimation(PAnimation_State _State)
	{
		AnimaionFSM.ChangeState(_State);
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


	std::shared_ptr<class UCollision> GetCollision()
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



protected:

private:
	float CurTime = 0.0f;
	ACameraActor* MainCamera = nullptr;
	
	UFSMStateManager AnimaionFSM;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;

	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;
	std::map<std::string, std::shared_ptr<class ASkill>> SkillMap;


	FVector Velocity = FVector::ZERO;
	bool IsDownableFloor = false;
	float GravityAccel = 0.0f;

	PlayerLogicValue LogicValue;
		
	void CheckKey(float _DeltaTime);
	void InitSkill();

};

