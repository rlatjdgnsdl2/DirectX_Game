#pragma once
struct FPlayerLogic
{
	FVector Velocity = FVector::ZERO;
	float GravityAccel = 0.0f;
	bool bIsMoveable = true;
	bool bIsJumpable = true;
	bool bIsProneable = true;
	bool bIsSkillable = true;
	bool bIsDownableFloor = true;

	bool bIsGround = false;
	bool bIsJumping = true;
	bool bIsFalling = true;
	bool bIsProne = false;
	bool bIsUsingSkill = false;

	int JumpCount = 0;
	int JumpCountMax = 3;

	void StartUltimateDrive() {
		bIsUsingSkill = true;
		bIsMoveable = true;
		bIsJumpable = false;
		bIsProneable = false;
		bIsSkillable = false;
	}
	void EndUltimateDrive() {
		bIsUsingSkill = false;
		bIsJumpable = true;
		bIsProneable = true;
		bIsSkillable = true;
	}

	void PlayProne() {
		bIsProne = true;
		bIsMoveable = false;
		bIsJumpable = true;
		bIsProneable = false;
		bIsSkillable = false;
	}

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
		bIsJumping = true;
		bIsGround = false;
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

struct FDamageInfo 
{
	unsigned long long Damage;
	int MaxHitCount;
	float HitDelay;
};

struct FPlayerStatus
{
	std::string Name = "";

	int Level =1;

	bool bIsFillable = true;
	bool IsFillable()
	{
		return bIsFillable;
	}
	void SetFillable(bool _Value)
	{
		bIsFillable = _Value;
	}
	void SetFillTrue()
	{
		bIsFillable = true;
	}
	void SetFillFalse()
	{
		bIsFillable = false;
	}


	float MaxHp = 60000;
	float PrevHp= 60000;
	float CurHp = 60000;
	bool bIsHpChange = false;
	float CurHpPercent =1.0f;
	float PrevHpPercent = 1.0f;

	void FillMaxHp()
	{
		if (!bIsFillable) { return; }
		PrevHp = CurHp;
		PrevHpPercent = CurHp / MaxHp;
		CurHp = MaxHp;
		CurHpPercent = CurHp / MaxHp;
		bIsHpChange = true;
	}

	float MaxMp =40000;
	float PrevMp = 40000;
	float CurMp = 40000;
	bool bIsMpChange = false;
	float CurMpPercent = 1.0f;
	float PrevMpPercent = 1.0f;

	void FillMaxMp()
	{
		if (!bIsFillable) { return; }
		PrevMp = CurMp;
		PrevMpPercent = CurMp / MaxMp;
		CurMp = MaxMp;
		CurMpPercent = CurMp / MaxMp;
		bIsMpChange = true;
	}

	void FillMaxHpMp()
	{
		FillMaxHp();
		FillMaxMp();
	}

	void UseMp(float _Mp)
	{
		PrevMp = CurMp;
		PrevMpPercent = CurMp / MaxMp;
		CurMp -= _Mp;
		if (CurMp < 0.0f)
		{
			CurMp = 0.0f;
		}
		CurMpPercent = CurMp / MaxMp;
		bIsMpChange = true;
	}

	float Damage = 999999999;
	
	void TakeHpPercentDamage(float _Percent) 
	{
		PrevHp = CurHp;
		PrevHpPercent = CurHp / MaxHp;
		CurHp -= MaxHp * _Percent;
		if (CurHp < 0.0f)
		{
			CurHp = 0.0f;
		}
		CurHpPercent = CurHp / MaxHp;
		bIsHpChange = true;
	}

	void TakeDamage(float _Damage)
	{
		PrevHp = CurHp;
		PrevHpPercent = CurHp / MaxHp;
		CurHp -= _Damage;
		if (CurHp < 0.0f)
		{
			CurHp = 0.0f;
		}
		CurHpPercent = CurHp / MaxHp;
		bIsHpChange = true;
	}
};
