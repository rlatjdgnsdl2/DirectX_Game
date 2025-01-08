#pragma once

enum class Z_ORDER
{
	Skill_PlayerFront = 10,
	Player,
	Skill_PlayerBack,
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

