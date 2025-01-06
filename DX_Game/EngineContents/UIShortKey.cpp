#include "PreCompile.h"
#include "UIShortKey.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>



UIShortKey::UIShortKey() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
}

UIShortKey::~UIShortKey() 
{

}
