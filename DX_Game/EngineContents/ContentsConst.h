#pragma once

class UContentsConst
{
public:
	// Color
	static const FVector SCOPE_COLOR;
	static const FVector COLLISIONING_COLOR;

	// ZPos
	inline static const float DAMAGESKIN_ZPOS					= 100.0F;

	inline static const float P_EFFECT_FRONT_ZPOS				= 200.0F;
	inline static const float PLAYER_ZPOS						= 300.0F;
	inline static const float P_EFFECT_BACK_ZPOS				= 400.0F;

	inline static const float M_EFFECT_FRONT_ZPOS				= 500.0F;
	inline static const float MONSTER_ZPOS						= 600.0F;
	inline static const float M_EFFECT_BACK_ZPOS				= 700.0F;

	inline static const float B_EFFECT_FRONT_ZPOS				= 800.0F;
	inline static const float BOSS_ZPOS							= 900.0f;		
	inline static const float B_EFFECT_BACK_ZPOS				= 1000.0F;

	inline static const float N_EFFECT_FRONT_ZPOS				= 1100.0F;
	inline static const float NPC_ZPOS							= 1200.0f;
	inline static const float N_EFFECT_BACK_ZPOS				= 1300.0F;

	inline static const float FOOTHOLD_ZPOS						= 1400.0f;

	inline static const float SKILL_COVER_ZPOS					= 1500.0f;

	inline static const float MAPOBJECT_NEAR_ZPOS				= 1600.0f;
	inline static const float MAPOBJECT_MIDDLE_ZPOS				= 17000.0f;
	inline static const float MAPOBJECT_FAR_ZPOS				= 1800.0f;

	inline static const float BACKGROUND_ZPOS					= 1900.0f;

	// Hp
	inline static const double FALLEN_WARRIOR_HP				= 300'0000'0000;
	inline static const double DUNKEL_HP						= 157'5000'0000'0000.0;
};

