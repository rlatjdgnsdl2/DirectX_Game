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

enum class PlayerState {
	Stand,
	Walk,
	Jump,
	Prone,
	UltimateDrive_StartEnd,
	UltimateDrive_KeyDown
};

