#pragma once

enum class Z_ORDER
{
	Skill_Front=100,
	Player=200,
	Skill_Back=300,
	NPC=400,
	FootHold=500,
	SkillCover=600,
	BackGround =700,
};


enum class Skill_Frame
{
	Start,
	KeyDown,
	End
};

enum class Player_State {
	None,
	Stand,
	Walk,
	Jump,
	Prone,
	Ultimate_Drive,
	Max
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





enum class Skill_Name {
	Ultimate_Drive,
};


