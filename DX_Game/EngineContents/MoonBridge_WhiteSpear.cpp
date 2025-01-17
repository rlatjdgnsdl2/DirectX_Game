#include "PreCompile.h"
#include "MoonBridge_WhiteSpear.h"
#include "MoonBridge_WhiteSpear_Map.h"
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>

#include "Player.h"

AMoonBridge_WhiteSpear::AMoonBridge_WhiteSpear()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\MoonBridge\\WhiteSpear");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());

	}
	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->CreateCollisionProfile("Boss");
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("FootHold");
	GetWorld()->CreateCollisionProfile("UI");
	GetWorld()->CreateCollisionProfile("EndArea");
	GetWorld()->CreateCollisionProfile("PlayerSkill");

	GetWorld()->GetMainCamera()->GetCameraComponent()->SetZSort(0,true);

	GetWorld()->SpawnActor<AMoonBridge_WhiteSpear_Map>();
}

AMoonBridge_WhiteSpear::~AMoonBridge_WhiteSpear()
{
}

void AMoonBridge_WhiteSpear::BeginPlay()
{
	AActor::BeginPlay();
	GetWorld()->GetMainPawn()->SetActorLocation(FVector(0.0f, 0.0f));
}
