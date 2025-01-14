#include "PreCompile.h"
#include "Dunkel.h"


ADunkel::ADunkel() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	{
		std::shared_ptr<class USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->AddZ(static_cast<float>(Z_ORDER::Player));
		DunkelAnimation.SetSpriteRenderer(SpriteRenderer);
	}
	DunkelAnimation.Init();
}

ADunkel::~ADunkel() 
{

}
