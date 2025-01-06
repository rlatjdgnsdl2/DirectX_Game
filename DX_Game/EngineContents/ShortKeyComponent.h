#pragma once
#include <EngineCore/ActorComponent.h>


//	Ό³Έν:
class UShortKeyComponent : public UActorComponent
{
public:
	UShortKeyComponent();
	virtual ~UShortKeyComponent();
	UShortKeyComponent(const UShortKeyComponent& _Other) = delete;
	UShortKeyComponent(UShortKeyComponent&& _Other) noexcept = delete;
	UShortKeyComponent& operator=(const UShortKeyComponent& _Other) = delete;
	UShortKeyComponent& operator=(UShortKeyComponent&& _Other) noexcept = delete;

	void RegisterShortKey(int _Key, std::string_view _FuncName) 
	{
		std::string UpperName = UEngineString::ToUpper(_FuncName);
		std::map<int, std::string>::iterator FindIter = ShortKeyMap.begin();
		std::map<int, std::string>::iterator EndIter = ShortKeyMap.end();
		for (; FindIter != EndIter; ++FindIter)
		{
			std::string FucName = FindIter->second;
			if (UpperName == FucName)
			{
				ShortKeyMap.erase(FindIter);
				break;
			}
		}	
		ShortKeyMap[_Key] = UpperName;
	};

	




protected:

private:
	std::map<int, std::string> ShortKeyMap;
	std::unordered_map<std::string, UEngineDelegate> FuncMap;


};

