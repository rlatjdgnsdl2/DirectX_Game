#pragma once

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
	void ChangeAnimation(std::string_view _AnimationName);

	virtual void Init() {}

protected:
	UFSMStateManager AnimationFSM;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
private:


};

