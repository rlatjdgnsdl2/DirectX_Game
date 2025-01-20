#pragma once
#include <EngineCore/ActorComponent.h>
#include <EngineBase/EngineDelegate.h>
#include "PlayerFunction.h"

//	Ό³Έν:
class UPlayerFuncManager : public UActorComponent
{
public:
	UPlayerFuncManager();
	virtual ~UPlayerFuncManager();
	UPlayerFuncManager(const UPlayerFuncManager& _Other) = delete;
	UPlayerFuncManager(UPlayerFuncManager&& _Other) noexcept = delete;
	UPlayerFuncManager& operator=(const UPlayerFuncManager& _Other) = delete;
	UPlayerFuncManager& operator=(UPlayerFuncManager&& _Other) noexcept = delete;

	virtual void BeginPlay() override;

	void SetFuncName(int _Key, std::string _FuncName)
	{
		std::string UpperName = UEngineString::ToUpper(_FuncName);
		std::map<int, std::string>::iterator FindIter = FuncNameMap.begin();
		std::map<int, std::string>::iterator EndIter = FuncNameMap.end();

		for (; FindIter != EndIter; ++FindIter)
		{
			std::string FindName = FindIter->second;
			if (FindName == UpperName)
			{
				FuncNameMap.erase(FindIter);
				break;
			}
		}
		if (FuncNameMap.contains(_Key))
		{
			FuncNameMap[_Key] = UpperName;
		}
		else
		{
			FuncNameMap.insert(std::make_pair(_Key, UpperName));
		}
	}

	std::string GetFuncName(int _Key)
	{
		if (FuncNameMap.contains(_Key))
		{
			return FuncNameMap[_Key];
		}
		return "";
	}

	void SetFunc(std::string _FuncName, UEngineDelegate& _Func)
	{
		std::string UpperName = UEngineString::ToUpper(_FuncName);
		if (FuncMap.contains(UpperName))
		{
			FuncMap[UpperName] = _Func;
		}
		else
		{
			FuncMap.insert(std::make_pair(UpperName, _Func));
		}
	}
	int GetKey(std::string _FuncName)
	{
		std::string UpperName = UEngineString::ToUpper(_FuncName);
		std::map<int, std::string>::iterator FindIter = FuncNameMap.begin();
		std::map<int, std::string>::iterator EndIter = FuncNameMap.end();
		for (; FindIter != EndIter; ++FindIter)
		{
			std::string FindName = FindIter->second;
			if (FindName == UpperName)
			{
				return FindIter->first;
			}
		}
		return -1;
	}

	UEngineDelegate GetFunc(std::string _FuncName)
	{
		std::string UpperName = UEngineString::ToUpper(_FuncName);
		if (FuncMap.contains(UpperName))
		{
			return FuncMap[UpperName];
		}
		else {
			return UEngineDelegate([]() {});
		}
	}

	


protected:

private:
	class APlayer* Player;
	std::map<int, std::string> FuncNameMap;
	std::map<std::string, UEngineDelegate> FuncMap;


	






};

