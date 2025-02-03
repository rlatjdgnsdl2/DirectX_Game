#pragma once


enum class EPlayer_State
{
	None = 0,

	// �⺻
	Idle,
	Move_Left,
	Move_Right,
	Prone,
	

	// skill
	Ultimate_Drive,
	Swift_Phantom,
	Rift_Break,

	// �����̻�
	KnockBack,
};

enum class EPlayer_Function 
{
	None = 0,
	Left,
	Right,
	Jump,
	Prone,
	Rope,
	Down,

	Swift_Phantom,
	Ultimate_Drive,
	Rift_Break,
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





