#pragma once

enum class Z_ORDER
{
	Skill_Front=100,
	Player,
	Skill_Back,
	Monster,
	Boss,
	NPC,
	FootHold,
	SkillCover,
	MapObject_Near,
	MapObject_Middle ,
	MapObject_Far ,
	BackGround ,
};


enum class Skill_Frame
{
	Start,
	Update,
	End
};



enum class PAnimation_State {
	None,
	Stand,
	Walk,
	Jump,
	Prone,
	Ultimate_Drive,
	Max
};

enum class DunkelAnim_State {
	None,
	Spawn,
	Stand,
	Knockback,

};





enum class Skill_Name {
	Ultimate_Drive,
};


