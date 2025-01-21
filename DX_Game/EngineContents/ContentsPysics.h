#pragma once



class UContentsPhysicsConst
{
public:
	static inline const float WalkSpeed = 125.0f;
	static inline const float SlipSpeed = 120.0f;
	static inline const float FloatDrag1 = 100000.0f;
	static inline const float FloatDrag2 = 10000.0f;
	static inline const float FloatCoefficient = 0.01f;
	static inline const float SwimForce = 120000.0f;
	static inline const float SwimSpeed = 140.0f;
	static inline const float FlyForce = 120000.0f;
	static inline const float FlySpeed = 200.0f;
	static inline const float GravityAcc = 2000.0f;
	static inline const float FallSpeed = 670.0f;
	static inline const float JumpSpeed = 555.0f;
	static inline const float MaxFriction = 2.0f;
	static inline const float MixFriction = 0.05f;
	static inline const float SwimSpeedDec = 0.9f;
	static inline const float FlyJumpDec = 0.35f;
	static inline const float WalkForce = 140000.0f;
	static inline const float WalkDrag = 80000.0f;
	static inline const float SlipForce = 60000.0f;

	static inline float PlayerWalkSpeed = 160.0f;
	static inline float PlayerJumpSpeed = 123.0f;
};




//	설명:
class UContentsPysics
{
public:
    static float ApplyGravity(float _Velocity, float _DeltaTime) {
        _Velocity += UContentsPhysicsConst::GravityAcc * _DeltaTime;
		float Result = (_Velocity < UContentsPhysicsConst::FallSpeed) ? _Velocity : UContentsPhysicsConst::FallSpeed;
		return Result;
    }
	static float ApplyWalkForce(float _Velocity, float _DeltaTime)
	{
		_Velocity += UContentsPhysicsConst::WalkForce * _DeltaTime;
		return (_Velocity > UContentsPhysicsConst::PlayerWalkSpeed) ? UContentsPhysicsConst::PlayerWalkSpeed : _Velocity;
	}



	static float CalculateSlipAcceleration(float _Mass = 70.0f) {
		return UContentsPhysicsConst::SlipForce / _Mass;
	}

	static float CalculateWalkAcceleration(float _Mass = 70.0f) {
		return (UContentsPhysicsConst::WalkForce / _Mass) - UContentsPhysicsConst::WalkDrag;
	}

	// 점프 계산
	static float ApplyJump(float _DeltaTime) {
		return UContentsPhysicsConst::JumpSpeed - UContentsPhysicsConst::GravityAcc * _DeltaTime;
	}
};

