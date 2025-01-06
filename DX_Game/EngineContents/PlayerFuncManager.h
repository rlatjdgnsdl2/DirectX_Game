#pragma once
#include <EngineCore/ActorComponent.h>
#include "PlayerFunc.h"

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

	void SetFunc(std::string _FuncName, UPlayerFunc& _Func)
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
	UPlayerFunc GetFunc(std::string _FuncName)
	{
		std::string UpperName = UEngineString::ToUpper(_FuncName);
		if (FuncMap.contains(UpperName))
		{
			return FuncMap[UpperName];
		}
		else {
			return UPlayerFunc();
		}
	}




protected:

private:
	class APlayer* Player = nullptr;
	std::map<int, std::string> FuncNameMap;
	std::unordered_map<std::string, UPlayerFunc> FuncMap;


};

