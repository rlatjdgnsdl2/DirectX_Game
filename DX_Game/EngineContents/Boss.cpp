#include "PreCompile.h"
#include "Boss.h"


ABoss::ABoss() 
{
	UMyCollision* Collision = GetCollision("Character");
	Collision->SetCollisionProfileName("Boss");
}

ABoss::~ABoss() 
{

}
