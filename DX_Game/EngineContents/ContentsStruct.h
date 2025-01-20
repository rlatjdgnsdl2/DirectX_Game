#pragma once
struct FPlayerLogic
{
	FVector Velocity = FVector::ZERO;
	float GravityAccel = 0.0f;
	bool bIsMoveable;
	bool bIsJumpable;
	bool bIsProneable;
	bool bIsSkillable;
	bool bIsDownableFloor;

	bool bIsGround = false;
	bool bIsJumping = true;
	bool bIsFalling = true;
	bool bIsProne = false;
	bool bIsUsingSkill = false;

	int JumpCount = 0;
	int JumpCountMax = 3;

	void SetGravityAccel(float _Accel)
	{
		GravityAccel = _Accel;
	}

	void SetVelocityX(float _X)
	{
		Velocity.X = _X;
	}

	void SetVelocityY(float _Y)
	{
		Velocity.Y = _Y;
	}

	void AddVelocityX(float _X)
	{
		Velocity.X += _X;
	}
	void AddVelocityY(float _Y)
	{
		Velocity.Y += _Y;
	}

	void ResetVelocity()
	{
		Velocity = FVector::ZERO;
	}

	void SetDownableFloor(bool _Value)
	{
		bIsDownableFloor = _Value;
	}

	bool GetDownableFloor()
	{
		return bIsDownableFloor;
	}

	void Init()
	{
		bIsMoveable = true;
		bIsJumpable = true;
		bIsProneable = true;
		bIsSkillable = true;
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
		bIsMoveable = true;
		bIsJumpable = true;
		JumpCount = 0;
	}
};
