#include "PreCompile.h"
#include "Job_Phantom.h"

#include "Player.h"

#include "PlayerFunction.h"



#include "Skill_UltimateDrive.h"
#include "Skill_SwiftPhantom.h"


UJob_Phantom::UJob_Phantom() 
{

	
	{
		ASkill_UltimateDrive* Skill = GetWorld()->SpawnActor<ASkill_UltimateDrive>().get();
		Skill->SetOwner(GetActor());
		Skill->SetActiveFalse();
		InsertSkill(EPlayer_Function::Ultimate_Drive, Skill);
	}

	{
		ASkill_SwiftPhantom* Skill = GetWorld()->SpawnActor<ASkill_SwiftPhantom>().get();
		Skill->SetOwner(GetActor());
		Skill->SetActiveFalse();
		InsertSkill(EPlayer_Function::Swift_Phantom, Skill);
	}
}

UJob_Phantom::~UJob_Phantom() 
{
	
}
