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

	
	void CreateState(Player_State _Key, std::function<void(float)> _UpdateFunction, std::function<void()> _Start = nullptr)
	{
		PlayerFSM.GetFSM().CreateState(static_cast<int>(_Key), _UpdateFunction, _Start);
	}

	void ChangeState(Player_State _State)
	{
		PlayerFSM.ChangeState(_State);
	}

	void Update(float _DeltaTime) {
		PlayerFSM.GetFSM().Update(_DeltaTime);
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

	UPlayerFSM& GetPlayerFSM()
	{
		return PlayerFSM;
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
	void SetSkillStart(std::string_view _SkillName, std::shared_ptr<class ASkill> _Skill)
	{
		std::string UpperName = UEngineString::ToUpper(_SkillName);
		if (SkillMap.contains(UpperName))
		{
			SkillMap[UpperName] = _Skill;
		}
	}

	void SetSkillEnd(std::string_view _SkillName)
	{
		std::string UpperName = UEngineString::ToUpper(_SkillName);
		if (SkillMap.contains(UpperName))
		{
			SkillMap[UpperName]=nullptr;
		}
	}




protected:

private:
	float DeltaTime = 0.0f;
	UPlayerFSM PlayerFSM;
	UPlayerAnimation PlayerAnimation;

	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;
	std::unordered_map<std::string_view, std::shared_ptr<class ASkill>> SkillMap;

	bool IsGround = true;
	bool IsJump = false;


	void Stand(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Prone(float _DeltaTime);
	void Ultimate_Drive(float _DeltaTime);
	
	void CheckKey(float _DeltaTime);
	


	

	




};

