#pragma once
#include <string>
#include <memory>

// Ό³Έν :
class UObject
{
public:
	ENGINEAPI UObject();
	ENGINEAPI virtual ~UObject() = 0;
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	std::string GetName() const{
		return Name;
	}

	std::string_view GetNameView() const{
		return Name.c_str();
	}

	virtual void SetName(std::string_view _Name){
		Name = _Name.data();
	}

	virtual bool IsActive(){
		return IsActiveValue && false == IsDestroyValue;
	}

	virtual bool IsDestroy(){
		return IsDestroyValue;
	}

	void Destroy(float _Time = 0.0f){
		DeathTime = _Time;
		if (0.0f < _Time){
			IsDeathTimeCheck = true;
			return;
		}
		IsDestroyValue = true;
	}

	virtual void ReleaseTimeCheck(float _DeltaTime)
	{
		if (false == IsDeathTimeCheck)
		{
			return;
		}

		CurDeathTime += _DeltaTime;

		if (DeathTime <= CurDeathTime)
		{
			IsDestroyValue = true;
		}
	}

	void SetActive(bool _IsActive)
	{
		IsActiveValue = _IsActive;
	}

	void SetActiveSwitch()
	{
		IsActiveValue = !IsActiveValue;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}

	void DebugOn()
	{
		IsDebugValue = true;
	}

	void DebugOff()
	{
		IsDebugValue = false;
	}

	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

protected:

private:
	std::string Name;
	bool IsDestroyValue = false;
	bool IsActiveValue = true;

	bool IsDeathTimeCheck = false;
	float DeathTime = 0.0f;
	float CurDeathTime = 0.0f;

	bool IsDebugValue = false;
};

