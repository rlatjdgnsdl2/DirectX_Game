#pragma once

enum class Z_ORDER
{
	Skill_Front=100,
	Player=200,
	Skill_Back=300,
	Monster=330,
	Boss=360,
	NPC=400,
	FootHold=500,
	SkillCover=600,
	MapObject_Near = 630,
	MapObject_Middle = 660,
	MapObject_Far = 690,
	BackGround =700,
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
	Stand
};





enum class Skill_Name {
	Ultimate_Drive,
};


