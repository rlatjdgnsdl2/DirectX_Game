#pragma once
#include <EngineCore/ActorComponent.h>


//	Ό³Έν:
class UJobComponent : public UActorComponent
{
public:
	UJobComponent();
	virtual ~UJobComponent();
	UJobComponent(const UJobComponent& _Other) = delete;
	UJobComponent(UJobComponent&& _Other) noexcept = delete;
	UJobComponent& operator=(const UJobComponent& _Other) = delete;
	UJobComponent& operator=(UJobComponent&& _Other) noexcept = delete;

	void InsertSkill(std::string_view _SkillName, std::shared_ptr<class ASkill> _Skill)
	{
		std::string UpperName = UEngineString::ToUpper(_SkillName);
		if (!SkillMap.contains(UpperName))
		{
			SkillMap.insert(std::make_pair(UpperName, _Skill.get()));
		}
	}

	class ASkill* GetSkill(std::string_view _SkillName)
	{
		std::string UpperName = UEngineString::ToUpper(_SkillName);
		if (SkillMap.contains(UpperName))
		{
			return SkillMap[UpperName];
		}
		return nullptr;
	}

protected:
	std::map<std::string, class ASkill*> SkillMap;
private:

};

