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

	virtual void BeginPlay() override;

	void InsertSkill(EPlayer_Function _Name, class ASkill* _Skill)
	{
		SkillMap.insert(std::make_pair(_Name, _Skill));
	}

	class ASkill* GetSkill(EPlayer_Function _Name)
	{
		if (SkillMap.contains(_Name))
		{
			return SkillMap[_Name];
		}
		return nullptr;
	}

protected:
	std::map<EPlayer_Function, class APlayerFunction*> DirFuncMap;
	std::map<EPlayer_Function, class ASkill*> SkillMap;
private:

};

