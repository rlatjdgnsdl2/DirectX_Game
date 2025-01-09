#include "PreCompile.h"
#include "Player.h"
#include "Skill_UltimateDrive.h"


void APlayer::InitSkill() {
	{
		std::shared_ptr<ASkill_UltimateDrive> Skill = GetWorld()->SpawnActor<ASkill_UltimateDrive>();
		Skill->SetActiveFalse();
		Skill->SetOwner(this);
		AddSkill("UltimateDrive", Skill);
	}
}