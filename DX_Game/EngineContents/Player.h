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

	template<typename SkillName>
	void SpawnSkill() {
		GetWorld()->SpawnActor<SkillName>();
	}


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

	FVector Gravity = FVector(0.0f, -9.8f, 0.0f);
	bool IsGround = false;
	bool IsJumping = false;
	bool IsFalling = false;
	bool IsAttacking = false;

	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
	std::shared_ptr<class USpriteRenderer> TestRenderer;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;
	




};

