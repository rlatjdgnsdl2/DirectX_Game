#pragma once
#include <EngineBase/FSMStateManager.h>


//	Ό³Έν:
class UAnimationManager
{
public:
	UAnimationManager();
	virtual ~UAnimationManager();
	UAnimationManager(const UAnimationManager& _Other) = delete;
	UAnimationManager(UAnimationManager&& _Other) noexcept = delete;
	UAnimationManager& operator=(const UAnimationManager& _Other) = delete;
	UAnimationManager& operator=(UAnimationManager&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetSpriteRenderer() {
		return SpriteRenderer;
	}

	void SetSpriteRenderer(std::shared_ptr<class USpriteRenderer> _SpriteRenderer) {
		SpriteRenderer = _SpriteRenderer;
	}

	UFSMStateManager& GetFSM()
	{
		return AnimationFSM;
	}

	template<typename EnumType>
	void CreateState(EnumType _Key, std::function<void()> _Start, std::function<void(float)> _UpdateFunction = nullptr)
	{
		AnimationFSM.CreateState(static_cast<int>(_Key), _UpdateFunction, _Start);
	}

	template<typename EnumType>
	void ChangeState(EnumType _Key)
	{
		AnimationFSM.ChangeState(static_cast<int>(_Key));
	}

	template<typename EnumType>
	EnumType GetCurStateValue() {
		return static_cast<EnumType>(AnimationFSM.GetCurStateValue<EnumType>());
	}

	template<typename EnumType>
	EnumType GetPrevStateValue() {
		return static_cast<EnumType>(AnimationFSM.GetPrevStateValue<EnumType>());
	}





	void ChangeAnimation(std::string_view _AnimationName);
	virtual void Init() {}

protected:
	UFSMStateManager AnimationFSM;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
private:


};

