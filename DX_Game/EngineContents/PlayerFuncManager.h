#pragma once
#include <EngineCore/ActorComponent.h>
#include <EngineBase/EngineDelegate.h>
#include "PlayerFunction.h"

//	설명:
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

	void SetFuncName(int _Key, EPlayer_Function _Name)
	{
		std::map<int, EPlayer_Function>::iterator FindIter = FuncNameMap.begin();
		std::map<int, EPlayer_Function>::iterator EndIter = FuncNameMap.end();

		// 기존에 등록되어있던 단축키 제거
		for (; FindIter != EndIter; ++FindIter)
		{
			EPlayer_Function FindName = FindIter->second;
			if (FindName == _Name)
			{
				FuncNameMap.erase(FindIter);
				break;
			}
		}
		// 새로운 단축키 등록
		FuncNameMap[_Key] = _Name;
	}

	EPlayer_Function GetFuncName(int _Key)
	{
		if (FuncNameMap.contains(_Key))
		{
			return FuncNameMap[_Key];
		}
		return EPlayer_Function::None;
	}

	void SetFunc(int _Key, EPlayer_Function _Name, UEngineDelegate& _Func)
	{
		SetFunc(_Name, _Func);
		SetFuncName(_Key, _Name);
	}


	void SetFunc(EPlayer_Function _Name, UEngineDelegate& _Func)
	{
		FuncMap[_Name] = _Func;
	}

	int GetKey(EPlayer_Function _Name)
	{
		std::map<int, EPlayer_Function>::iterator FindIter = FuncNameMap.begin();
		std::map<int, EPlayer_Function>::iterator EndIter = FuncNameMap.end();
		for (; FindIter != EndIter; ++FindIter)
		{
			EPlayer_Function FindName = FindIter->second;
			if (FindName == _Name)
			{
				return FindIter->first;
			}
		}
		return -1;
	}

	UEngineDelegate GetFunc(int _Key)
	{
		EPlayer_Function Name =GetFuncName(_Key);
		if (FuncMap.contains(Name))
		{
			return FuncMap[Name];
		}
		else {
			return UEngineDelegate([]() {});
		}
	}
	UEngineDelegate GetFunc(EPlayer_Function _Name)
	{
		if (FuncMap.contains(_Name))
		{
			return FuncMap[_Name];
		}
		else {
			return UEngineDelegate([]() {});
		}
	}

protected:

private:
	class APlayer* Player;
	std::map<int, EPlayer_Function> FuncNameMap;
	std::map<EPlayer_Function, UEngineDelegate> FuncMap;










};

