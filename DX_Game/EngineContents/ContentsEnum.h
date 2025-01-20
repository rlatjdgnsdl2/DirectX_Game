#pragma once

enum class Z_ORDER
{
	Skill_Front = 100,
	Player = 200,
	Skill_Back = 300,
	Monster = 400,
	Boss = 500,
	NPC = 600,
	FootHold = 700,
	SkillCover =800,
	MapObject_Near=900,
	MapObject_Middle = 1000,
	MapObject_Far=1100,
	BackGround = 1200,
};

enum class Skill_Frame
{
	First,
	Second,
	Third
};


enum class DunkelAnim_State {
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





