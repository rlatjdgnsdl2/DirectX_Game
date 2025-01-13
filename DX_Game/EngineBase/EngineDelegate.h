#pragma once
#include <functional>

// Ό³Έν :
class UEngineDelegate
{
public:
	ENGINEAPI UEngineDelegate();
	ENGINEAPI UEngineDelegate(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	ENGINEAPI  ~UEngineDelegate();

	ENGINEAPI bool IsEmpty()
	{
		bool EmptyValue = Functions.empty();
		return EmptyValue;
	}

	ENGINEAPI void operator+=(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	ENGINEAPI void operator()()
	{
		for (std::function<void()>& Function : Functions) {
			Function();
		}
	}

	ENGINEAPI void Clear()
	{
		Functions.clear();
	}

protected:

private:
	std::list<std::function<void()>> Functions;
};

