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

	bool IsEmpty()
	{
		bool EmptyValue = Functions.empty();
		return EmptyValue;
	}

	void operator+=(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	void operator()()
	{
		for (std::function<void()>& Function : Functions) {
			Function();
		}
	}

	void Clear()
	{
		Functions.clear();
	}

protected:

private:
	std::list<std::function<void()>> Functions;
};

