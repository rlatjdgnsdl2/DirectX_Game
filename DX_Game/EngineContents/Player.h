#pragma once
#include <EngineCore/Pawn.h>
#include "PlayerAnimation.h"
#include "PlayerFSM.h"


class PlayerBool 
{
public:
	bool IsMoveAbleValue = true;
	bool IsJumpAbleValue = true;

	bool IsGroundValue = false;
	bool IsJumpingValue = true;
	bool IsFallingValue = true;
	bool IsProneValue = false;

	bool IsSkillValue = false;
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

	bool IsMoveAble() const
	{
		return BoolValue.IsMoveAbleValue;
	}

	bool IsJumpAble() const
	{
		return BoolValue.IsJumpAbleValue;
	}

	bool IsGround() const
	{
		return BoolValue.IsGroundValue;
	}

	bool IsJump() const
	{
		return BoolValue.IsJumpingValue;
	}

	bool IsFalling() const
	{
		return BoolValue.IsFallingValue;
	}

	bool IsProne() const
	{
		return BoolValue.IsProneValue;
	}

	bool IsSkill() const
	{
		return BoolValue.IsSkillValue;
	}

	void SetMoveAble(bool _Value)
	{
		BoolValue.IsMoveAbleValue = _Value;
	}

	void SetJumpAble(bool _Value)
	{
		BoolValue.IsJumpAbleValue = _Value;
	}

	void SetGround(bool _Value)
	{
		BoolValue.IsGroundValue = _Value;
	}

	void SetJump(bool _Value)
	{
		BoolValue.IsJumpingValue = _Value;
	}

	void SetFalling(bool _Value)
	{
		BoolValue.IsFallingValue = _Value;
	}

	void SetProne(bool _Value)
	{
		BoolValue.IsProneValue = _Value;
	}

	void SetSkill(bool _Value)
	{
		BoolValue.IsSkillValue = _Value;
	}


	void Gravity(float _DeltaTime);

protected:

private:
	float DeltaTime = 0.0f;
	UPlayerAnimation PlayerAnimation;
	FVector PrevLocation;
	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;
	std::map<std::string, std::shared_ptr<class ASkill>> SkillMap;



	PlayerBool BoolValue;

	FVector JumpVector = FVector(0.0f, 123.0f, 0.0f);
	FVector GravityForce = FVector::ZERO;

	
	
	void CheckKey(float _DeltaTime);
	void InitSkill();
	


	

	




};

