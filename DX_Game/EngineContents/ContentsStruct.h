#pragma once
struct FPlayerLogic
{
	bool bIsMoveAble = true;
	bool bIsJumpAble = true;
	bool bIsProneAble = true;
	bool bIsSkillAble = true;

	bool bIsGround = false;
	bool bIsJumping = true;
	bool bIsFalling = true;
	bool bIsProne = false;

	bool bIsUsingSkill = false;

	int JumpCount = 0;
	int JumpCountMax = 3;

	void Init()
	{
		bIsMoveAble = true;
		bIsJumpAble = true;
		bIsProneAble = true;
		bIsSkillAble = true;
		bIsGround = false;
		bIsJumping = true;
		bIsFalling = true;
		bIsProne = false;
		bIsUsingSkill = false;
		JumpCount = 0;
		JumpCountMax = 3;
	}

	void PlusJumpCount()
	{
		JumpCount++;
	}
	void StartFalling() {
		bIsFalling = true;
		bIsJumping = false;
	}
	void StartJump()
	{
		JumpCount = 1;
		bIsGround = false;
		bIsJumping = true;
		bIsFalling = false;
	}

	bool IsJumpCountMax()
	{
		return JumpCount >= JumpCountMax;
	}

	void SetGroundTrue()
	{
		bIsGround = true;
		bIsFalling = false;
		bIsJumping = false;
		bIsMoveAble = true;
		bIsJumpAble = true;
		JumpCount = 0;
	}
};
