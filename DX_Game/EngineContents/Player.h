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

	
	void AnimationUpdate(float _DeltaTime) {
		PlayerAnimation.GetFSM().Update(_DeltaTime);
	}

	bool CheckAnimNode(PAnimation_State _CurAnimState, PAnimation_State _NextAnimState)
	{
		return PlayerAnimation.CheckAnimNode(_CurAnimState, _NextAnimState);
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
		return IsMoveAbleValue;
	}

	bool IsJumpAble() const
	{
		return IsJumpAbleValue;
	}

	bool IsGround() const
	{
		return IsGroundValue;
	}

	bool IsJump() const
	{
		return IsJumpingValue;
	}

	bool IsFalling() const
	{
		return IsFallingValue;
	}

	bool IsProne() const
	{
		return IsProneValue;
	}

	bool IsSkill() const
	{
		return IsSkillValue;
	}

	void SetMoveAble(bool _Value)
	{
		IsMoveAbleValue = _Value;
	}

	void SetJumpAble(bool _Value)
	{
		IsJumpAbleValue = _Value;
	}

	void SetGround(bool _Value)
	{
		IsGroundValue = _Value;
	}

	void SetJump(bool _Value)
	{
		IsJumpingValue = _Value;
	}

	void SetFalling(bool _Value)
	{
		IsFallingValue = _Value;
	}

	void SetProne(bool _Value)
	{
		IsProneValue = _Value;
	}

	void SetSkill(bool _Value)
	{
		IsSkillValue = _Value;
	}


protected:

private:
	float DeltaTime = 0.0f;
	UPlayerAnimation PlayerAnimation;
	FVector PrevLocation;
	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;
	std::map<std::string, std::shared_ptr<class ASkill>> SkillMap;

	bool IsMoveAbleValue = true;
	bool IsJumpAbleValue = true;

	bool IsGroundValue = true;
	bool IsJumpingValue = false;
	bool IsFallingValue = false;
	bool IsProneValue = false;

	bool IsSkillValue = false;	
	
	void CheckKey(float _DeltaTime);
	void InitSkill();
	


	

	




};

