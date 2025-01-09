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

	void SetSpriteRenderer(std::shared_ptr<class USpriteRenderer> _SpriteRenderer) {
		SpriteRenderer = _SpriteRenderer;
	}
	std::shared_ptr<class USpriteRenderer> GetSpriteRenderer() {
		return SpriteRenderer;
	}
	UFSMStateManager& GetFSM()
	{
		return AnimationFSM;
	}

	template<typename EnumType>
	void CreateState(EnumType _Key, std::function<void()> _Start = nullptr,
		std::function<void()> _End = nullptr)
	{
		AnimationFSM.CreateState(static_cast<int>(_Key), _Start, _End);
	}

	template<typename EnumType>
	void ChangeState(EnumType _Key)
	{
		AnimationFSM.ChangeState(static_cast<int>(_Key));
	}



	void ChangeAnimation(std::string_view _AnimationName);
	virtual void Init() {}

protected:
	UFSMStateManager AnimationFSM;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
private:


};

