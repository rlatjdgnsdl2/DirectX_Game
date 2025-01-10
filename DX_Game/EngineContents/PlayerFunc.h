#pragma once
#include <EngineBase/EngineDelegate.h>

//	Ό³Έν:
class UPlayerFunc
{
public:
	UPlayerFunc();
	virtual ~UPlayerFunc();

	bool IsAllEmpty()
	{
		if (Event.IsEmpty() && DownEvent.IsEmpty() && PressEvent.IsEmpty() && UpEvent.IsEmpty() && FreeEvent.IsEmpty())
		{
			return true;
		}
		return false;
	}
	bool IsEventEmpty()
	{
		if (Event.IsEmpty())
		{
			return true;
		}
		return false;
	}
	bool IsDownEventEmpty()
	{
		if (DownEvent.IsEmpty())
		{
			return true;
		}
		return false;
	}
	bool IsPressEventEmpty()
	{
		if (PressEvent.IsEmpty())
		{
			return true;
		}
		return false;
	}
	bool IsUpEventEmpty()
	{
		if (UpEvent.IsEmpty())
		{
			return true;
		}
		return false;
	}
	bool IsFreeEventEmpty()
	{
		if (FreeEvent.IsEmpty())
		{
			return true;
		}
		return false;
	}


	void AddEvent(std::function<void()> _Event)
	{
		Event += _Event;
	}

	void AddDownEvent(std::function<void()> _Event)
	{
		DownEvent += _Event;
	}
	void AddPressEvent(std::function<void()> _Event)
	{
		PressEvent += _Event;
	}
	void AddUpEvent(std::function<void()> _Event)
	{
		UpEvent += _Event;
	}
	void AddFreeEvent(std::function<void()> _Event)
	{
		FreeEvent += _Event;
	}

	void operator()()
	{
		Event();
	}

	void Down()
	{
		DownEvent();
	}
	void Press()
	{
		PressEvent();
	}
	void Up()
	{
		UpEvent();
	}
	void Free()
	{
		FreeEvent();
	}




protected:

private:
	UEngineDelegate Event;
	UEngineDelegate DownEvent;
	UEngineDelegate PressEvent;
	UEngineDelegate UpEvent;
	UEngineDelegate FreeEvent;

};

