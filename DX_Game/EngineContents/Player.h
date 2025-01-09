#pragma once
#include <EngineCore/Pawn.h>

//	����:
class APlayer : public APawn
{
public:
	APlayer();
	virtual ~APlayer();
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;


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
	UFSMStateManager PlayerState;
	UFSMStateManager SkillState;

	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
	std::shared_ptr<class UPlayerFuncManager> PlayerFuncManager;

	std::shared_ptr<class ASkill_UltimateDrive> UltimateDrive;

	

	




};

