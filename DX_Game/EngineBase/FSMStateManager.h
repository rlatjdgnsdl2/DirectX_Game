#pragma once
#include <functional>
#include <map>
#include "EngineDebug.h"

// ���� :
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
			MSGASSERT("�̹� �����ϴ� ������Ʈ�� �� ������� �߽��ϴ�.");
			return;
		}

		States[_Key].UpdateFunction = _UpdateFunction;
		States[_Key].StartFunction = _Start;
	}

	ENGINEAPI void Update(float _DeltaTime)
	{
		if (nullptr == CurState)
		{
			MSGASSERT("���°� �������� ���� ������Ʈ�ӽ� �Դϴ�.");
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
		PrevState = CurState;
		PrevStateValue = CurStateValue;
		if (false == States.contains(_Key))
		{
			MSGASSERT("�������� ���� ������Ʈ�� ü���� �Ϸ��� �߽��ϴ�.");
			return;
		}
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

