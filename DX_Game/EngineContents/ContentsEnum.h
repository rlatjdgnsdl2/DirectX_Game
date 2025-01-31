#pragma once


enum class EPlayer_State
{
	None = 0,
	Idle,
	Move_Left,
	Move_Right,
	Prone,
	Jump,
	Ultimate_Drive,
	NormalAttack,
	KnockBack,
};

enum class EPlayer_Function 
{
	None = 0,
	Left,
	Right,
	Up,
	Down,
	Swift_Phantom,
	Ultimate_Drive,
};

enum class ESkill_Frame
{
	First,
	Second,
	Third
};

enum class EDunkelAnim_State {
	None,
	Die,
	Down,
	Force,
	Knockback,
	Meteo,
	Slash_End,
	Slash_Start,
	Spawn,
	Stand,
	Sword,
	Up
};


enum class EMonster_State {
	None,
	Attack,
	NoDamageMode,
	Die,
	Hit,
	Move,
	Spawn,
	Stand,
	SelfDestroy
};





