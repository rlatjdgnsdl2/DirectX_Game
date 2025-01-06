#pragma once
#include <EngineCore/Pawn.h>

//	Ό³Έν:
class APlayer : public APawn
{
public:
	APlayer();
	virtual ~APlayer();
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;

	class USpriteRenderer* GetSprtieRenderer()
	{
		return SpriteRenderer.get();
	}
	float GetDeltaTime() const
	{
		return DeltaTime;
	}

protected:

private:
	float DeltaTime = 0.0f;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
	std::shared_ptr<class USpriteRenderer> TestRenderer;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;
	




};

