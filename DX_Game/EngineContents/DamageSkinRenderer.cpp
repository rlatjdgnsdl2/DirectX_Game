#include "PreCompile.h"
#include "DamageSkinRenderer.h"


DamageSkinRenderer::DamageSkinRenderer() 
{
	SetMesh("Rect");
	SetMaterial("DamageSkinMaterial");

	GetRenderUnit().ConstantBufferLinkData("ResultColor", ColorData);
	GetRenderUnit().ConstantBufferLinkData("FSpriteData", SpriteData);
	GetRenderUnit().ConstantBufferLinkData("FUVValue", UVValue);
	GetRenderUnit().ConstantBufferLinkData("TimeColor", Alpha);

	UVValue.PlusUVValue = { 0.0f, 0.0f, 0.0f, 0.0f };
	SpriteData.CuttingPos = { 0.0f, 0.0f };
	SpriteData.CuttingSize = { 1.0f, 1.0f };
	SpriteData.Pivot = { 0.5f, 0.5f };

	ColorData.PlusColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	ColorData.MulColor = { 1.0f, 1.0f, 1.0f, 1.0f };

}

DamageSkinRenderer::~DamageSkinRenderer() 
{

}

void DamageSkinRenderer::ComponentTick(float _DeltaTime)
{
	USpriteRenderer::ComponentTick(_DeltaTime);
	ContinueTime -= _DeltaTime;
	if (ContinueTime < 0.0f)
	{
		Alpha -= _DeltaTime;
		if (Alpha < 0.0f)
		{
			Alpha = 0.0f;
		}
	}
}
