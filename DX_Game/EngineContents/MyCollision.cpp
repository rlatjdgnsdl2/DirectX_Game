#include "PreCompile.h"
#include "MyCollision.h"


UMyCollision::UMyCollision() 
{
	Unit.SetMesh("Rect");
	Unit.SetMaterial("MyCollisionDebugMaterial");
	Unit.SetTexture("ImageTexture", "DebugCollisionBase.png");
}

UMyCollision::~UMyCollision() 
{

}

void UMyCollision::DebugRender(UEngineCamera* _Camera, float _DeltaTime)
{

	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();
	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;


	Unit.ConstantBufferLinkData("FTransform", GetTransformRef());
	FVector Color = { 0.0f, 1.0f, 0.0f };
	FSpriteData SpriteData;
	Unit.ConstantBufferLinkData("FSpriteData", SpriteData);
	Unit.ConstantBufferLinkData("OutColor", Color);
	Unit.Render(_Camera, _DeltaTime);
}
