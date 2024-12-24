#pragma once
#include <memory>
#include "EngineDefine.h"



// 설명 :
class UObject : public std::enable_shared_from_this<UObject>
{
public:
	ENGINEAPI UObject();
	ENGINEAPI virtual ~UObject() = 0;
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	template<typename ChildPtrType>
	std::shared_ptr<ChildPtrType> GetThis()
	{
		static_assert(std::is_base_of_v<UObject, ChildPtrType>, "UObject를 상속받지 않은 클래스를 GetThis하려고 했습니다.");
		return std::dynamic_pointer_cast<ChildPtrType>(shared_from_this());
	}

	// name
	std::string GetName() const
	{
		return Name;
	}
	std::string_view GetNameView() const
	{
		return Name.c_str();
	}
	virtual void SetName(std::string_view _Name)
	{
		Name = _Name.data();
	}

	virtual bool IsActive()
	{
		return IsActiveValue && false == IsDestroyValue;
	}
	virtual bool IsDestroy()
	{
		return IsDestroyValue;
	}

	void Destroy(float _Time = 0.0f)
	{
		DeathTime = _Time;
		if (0.0f < _Time)
		{
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

	int GetOrder()
	{
		return Order;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

protected:

private:
	std::string Name;

	int Order = 0;

	bool IsDestroyValue = false;
	bool IsActiveValue = true;

	bool IsDeathTimeCheck = false;
	float DeathTime = 0.0f;
	float CurDeathTime = 0.0f;

	bool IsDebugValue = false;
};

