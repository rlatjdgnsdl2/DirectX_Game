#pragma once
#include <EngineCore/ActorComponent.h>


//	Ό³Έν:
class UJob : public UActorComponent
{
public:
	UJob();
	virtual ~UJob();
	UJob(const UJob& _Other) = delete;
	UJob(UJob&& _Other) noexcept = delete;
	UJob& operator=(const UJob& _Other) = delete;
	UJob& operator=(UJob&& _Other) noexcept = delete;

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

