#pragma once
#include <EngineCore/ActorComponent.h>


//	Ό³Έν:
class AJob : public UActorComponent
{
public:
	AJob();
	virtual ~AJob();
	AJob(const AJob& _Other) = delete;
	AJob(AJob&& _Other) noexcept = delete;
	AJob& operator=(const AJob& _Other) = delete;
	AJob& operator=(AJob&& _Other) noexcept = delete;

	void InsertSkill(std::string_view _SkillName, std::shared_ptr<class ASkill> _Skill)
	{
		std::string UpperName = UEngineString::ToUpper(_SkillName);
		if (!SkillMap.contains(UpperName))
		{
			SkillMap.insert(std::make_pair(UpperName, _Skill));
		}
	}

	std::shared_ptr<class ASkill> GetSkill(std::string_view _SkillName)
	{
		std::string UpperName = UEngineString::ToUpper(_SkillName);
		if (SkillMap.contains(UpperName))
		{
			return SkillMap[UpperName].lock();
		}
		return nullptr;
	}

protected:
	std::map<std::string, std::weak_ptr<class ASkill>> SkillMap;
private:

};

