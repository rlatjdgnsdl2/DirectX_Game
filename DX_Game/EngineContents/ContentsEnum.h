#pragma once

enum class Z_ORDER
{
	Skill_Front=1000,
	Player=2000,
	Skill_Back=3000,
	NPC,
	Foot,
	Back
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


