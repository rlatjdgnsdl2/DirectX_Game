#include "PreCompile.h"
#include "AnimationManager.h"


UAnimationManager::UAnimationManager()
{

}

UAnimationManager::~UAnimationManager()
{

}

void UAnimationManager::ChangeAnimation(std::string_view _AnimationName)
{
	SpriteRenderer->ChangeAnimation(_AnimationName);
}
