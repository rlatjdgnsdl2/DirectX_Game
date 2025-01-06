#pragma once
#include <EngineBase/EngineDelegate.h>

//	Ό³Έν:
class UPlayerFunc
{
public:
	UPlayerFunc();
	virtual ~UPlayerFunc();
	/*UPlayerFunc(const UPlayerFunc& _Other) = delete;
	UPlayerFunc(UPlayerFunc&& _Other) noexcept = delete;
	UPlayerFunc& operator=(const UPlayerFunc& _Other) = delete;
	UPlayerFunc& operator=(UPlayerFunc&& _Other) noexcept = delete;*/

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
	UEngineDelegate DownEvent;
	UEngineDelegate PressEvent;
	UEngineDelegate UpEvent;
	UEngineDelegate FreeEvent;

};

