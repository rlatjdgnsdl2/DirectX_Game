#pragma once
#include <EngineBase/EngineDelegate.h>

//	Ό³Έν:
class UPlayerFunc
{
public:
	UPlayerFunc();
	virtual ~UPlayerFunc();
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

