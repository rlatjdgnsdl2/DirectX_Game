#pragma once

//	Ό³Έν:
class UPlayerFSM
{
public:
	UPlayerFSM();
	virtual ~UPlayerFSM();
	UPlayerFSM(const UPlayerFSM& _Other) = delete;
	UPlayerFSM(UPlayerFSM&& _Other) noexcept = delete;
	UPlayerFSM& operator=(const UPlayerFSM& _Other) = delete;
	UPlayerFSM& operator=(UPlayerFSM&& _Other) noexcept = delete;

	UFSMStateManager& GetFSM()
	{
		return FSM;
	}
	template<typename EnumType>
	void CreateState(EnumType _Key, std::function<void(float)> _UpdateFunction, std::function<void()> _Start = nullptr)
	{
		FSM.CreateState(static_cast<int>(_Key), _UpdateFunction, _Start);
	}

	template<typename EnumType>
	void ChangeState(EnumType _Key)
	{
		FSM.ChangeState(static_cast<int>(_Key));
	}

protected:

private:
	UFSMStateManager FSM;
};

