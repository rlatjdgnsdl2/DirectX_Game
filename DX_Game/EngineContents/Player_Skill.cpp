#include "PreCompile.h"
#include "Player.h"
#include "Skill_UltimateDrive.h"
#include "Skill_SwiftPhantom.h"


void APlayer::InitSkill() {
	{
		std::shared_ptr<ASkill_UltimateDrive> Skill = GetWorld()->SpawnActor<ASkill_UltimateDrive>();
		Skill->SetActiveFalse();
		Skill->SetOwner(this);
		AddSkill("UltimateDrive", Skill);
	}

	{
		std::shared_ptr<ASkill_SwiftPhantom> Skill = GetWorld()->SpawnActor<ASkill_SwiftPhantom>();
		Skill->SetActiveFalse();
		Skill->SetOwner(this);
		AddSkill("SwiftPhantom", Skill);
	}

}