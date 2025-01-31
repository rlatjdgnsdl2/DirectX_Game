#pragma once



class UContentsPhysicsConst
{
public:
	static inline const float GravityAcc = 2000.0f;
	static inline const float FallSpeed = 670.0f;

	static inline const float WalkSpeed = 285.0f;
	static inline const float WalkForce = 140000.0f;
	static inline const float WalkDrag = 80000.0f;

	static inline const float SlipSpeed = 120.0f;
	static inline const float SlipForce = 60000.0f;
	static inline const float JumpSpeed = 678.0f;

	/*static inline const float FloatDrag1 = 100000.0f;
	static inline const float FloatDrag2 = 10000.0f;
	static inline const float FloatCoefficient = 0.01f;
	static inline const float SwimForce = 120000.0f;
	static inline const float SwimSpeed = 140.0f;
	static inline const float FlyForce = 120000.0f;
	static inline const float FlySpeed = 200.0f;*/
	/*static inline const float MaxFriction = 2.0f;
	static inline const float MixFriction = 0.05f;
	static inline const float SwimSpeedDec = 0.9f;
	static inline const float FlyJumpDec = 0.35f;*/
};

//	Ό³Έν:
class UContentsPysics
{
public:
	static float ApplyGravity(float _VelocityY, float _DeltaTime)
	{
		float Result = _VelocityY - UContentsPhysicsConst::GravityAcc * _DeltaTime;
		if (Result < -UContentsPhysicsConst::FallSpeed)
		{
			Result = -UContentsPhysicsConst::FallSpeed;
		}
		return Result;
	}

	static float ApplyWalk(float _Value)
	{
		float Result =0.0f;
		Result = UEngineMath::Lerp(0.0f, UContentsPhysicsConst::WalkSpeed, UEngineMath::Clamp(_Value , 0.0f, 1.0f));
		return Result;
	}

};

