#pragma once
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

#include <vector>
#include <functional>



enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};

class UEngineInput
{
public:
	~UEngineInput();
	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;
private:
	class UEngineKey
	{
	public:
		UEngineKey() {}
		UEngineKey(int _Key) : Key(_Key) {}
		int Key = -1;
		bool IsDown = false;
		bool IsPress = false;
		bool IsUp = false;
		bool IsFree = true;
		float PressTime = 0.0f;
		float FreeTime = 0.0f;
		std::vector<std::function<void()>> PressEvents;
		std::vector<std::function<void()>> DownEvents;
		std::vector<std::function<void()>> UpEvents;
		std::vector<std::function<void()>> FreeEvents;

		void EventCheck();
		void KeyCheck(float _DeltaTime);
	};

	ENGINEAPI static UEngineInput& GetInst();
	ENGINEAPI static void EventCheck(float _DeltaTime);

public:
	ENGINEAPI static void KeyCheck(float _DeltaTime);
	ENGINEAPI static bool IsAllFree() 
	{
		for (auto& Key : GetInst().Keys)
		{
			if (Key.second.IsDown || Key.second.IsPress || Key.second.IsUp)
			{
				return false;
			}
		}
		return true;
	};


	ENGINEAPI static bool IsDoubleClick(int _KeyIndex, float _Time)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}
		return GetInst().Keys[_KeyIndex].IsDown && GetInst().Keys[_KeyIndex].FreeTime < _Time;
	}

	ENGINEAPI static bool IsDown(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}
		return GetInst().Keys[_KeyIndex].IsDown;
	}

	ENGINEAPI static bool IsUp(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}
		return GetInst().Keys[_KeyIndex].IsUp;
	}

	ENGINEAPI static bool IsPress(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}
		return GetInst().Keys[_KeyIndex].IsPress;
	}

	ENGINEAPI static float IsPressTime(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}
		return GetInst().Keys[_KeyIndex].PressTime;
	}


	ENGINEAPI static bool IsFree(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}
		return GetInst().Keys[_KeyIndex].IsFree;
	}

	ENGINEAPI static void BindAction(int _KeyIndex, KeyEvent _EventType, std::function<void()> _Function);

protected:

private:
	std::map<int, UEngineKey> Keys;
	UEngineInput();
};

