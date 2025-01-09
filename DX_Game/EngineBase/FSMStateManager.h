#pragma once
#include <functional>
#include <map>
#include "EngineDebug.h"

// 설명 :
class UFSMStateManager
{
public:
	// constrcuter destructer
	ENGINEAPI UFSMStateManager() {}
	ENGINEAPI ~UFSMStateManager() {}

	// delete Function
	UFSMStateManager(const UFSMStateManager& _Other) = delete;
	UFSMStateManager(UFSMStateManager&& _Other) noexcept = delete;
	UFSMStateManager& operator=(const UFSMStateManager& _Other) = delete;
	UFSMStateManager& operator=(UFSMStateManager&& _Other) noexcept = delete;

	class FSMState
	{
	public:
		std::function<void()> StartFunction = nullptr;
		std::function<void(float)> UpdateFunction = nullptr;
		std::function<void()> EndFunction = nullptr;
	};

	template<typename EnumType>
	ENGINEAPI void CreateState(EnumType _Key, std::function<void(float)> _UpdateFunction, std::function<void()> _Start = nullptr)
	{
		CreateState(static_cast<int>(_Key), _UpdateFunction, _Start);
	}

	ENGINEAPI void CreateState(int _Key, std::function<void(float)> _UpdateFunction, std::function<void()> _Start = nullptr)
	{
		if (true == States.contains(_Key))
		{
			MSGASSERT("이미 존재하는 스테이트를 또 만들려고 했습니다.");
			return;
		}

		States[_Key].UpdateFunction = _UpdateFunction;
		States[_Key].StartFunction = _Start;
	}

	ENGINEAPI void Update(float _DeltaTime)
	{
		if (nullptr == CurState)
		{
			MSGASSERT("상태가 지정되지 않은 스테이트머신 입니다.");
			return;
		}
		if (CurState->UpdateFunction != nullptr) {
			CurState->UpdateFunction(_DeltaTime);
		}
	}

	template<typename EnumType>
	ENGINEAPI void ChangeState(EnumType _Key)
	{
		ChangeState(static_cast<int>(_Key));
	}

	ENGINEAPI void ChangeState(int _Key)
	{
		if (false == States.contains(_Key))
		{
			MSGASSERT("만든적이 없는 스테이트로 체인지 하려고 했습니다.");
			return;
		}
		PrevState = CurState;
		PrevStateValue = CurStateValue;
		CurStateValue = _Key;
		CurState = &States[_Key];
		if (nullptr != CurState->StartFunction)
		{
			CurState->StartFunction();
		}
	}


	template<typename EnumType>
	ENGINEAPI EnumType GetCurStateValue()
	{
		return static_cast<EnumType>(CurStateValue);
	}
	template<typename EnumType>
	ENGINEAPI EnumType GetPrevStateValue()
	{
		return static_cast<EnumType>(PrevStateValue);
	}




protected:


private:
	FSMState* CurState = nullptr;
	FSMState* PrevState = nullptr;
	std::map<int, FSMState> States;
	int CurStateValue = 0;
	int PrevStateValue = 0;
};

