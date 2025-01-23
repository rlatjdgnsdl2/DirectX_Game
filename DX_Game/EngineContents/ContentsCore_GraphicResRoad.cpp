#include "PreCompile.h"
#include "ContentsCore.h"

void UContentsCore::ContentsDepthStencilInit() 
{

}
void UContentsCore::ContentsTextureInit() 
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsShader"))
		{
			MSGASSERT("EngineShader 폴더를 찾지 못했습니다.");
			return;
		}
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}
}
void UContentsCore::ContentsMeshInit() 
{

}
void UContentsCore::ContentsBlendInit() 
{

}
void UContentsCore::ContentsRasterizerStateInit() 
{
	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		UEngineRasterizerState::Create("MyCollisionDebugRas", Desc);
	}
}
void UContentsCore::ContentsShaderInit() 
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("ContentsShader");

	std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

	for (size_t i = 0; i < ShaderFiles.size(); i++)
	{
		UEngineShader::ReflectionCompile(ShaderFiles[i]);
	}
}
void UContentsCore::ContentsMaterialInit() 
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyCollisionDebugMaterial");
		Mat->SetVertexShader("ContentsCollisonDebugShader.fx");
		Mat->SetPixelShader("ContentsCollisonDebugShader.fx");
		Mat->SetDepthStencilState("CollisionDebugDepth");
		Mat->SetRasterizerState("CollisionDebugRas");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("DamageSkinMaterial");
		Mat->SetVertexShader("DamageSkinShader.fx");
		Mat->SetPixelShader("DamageSkinShader.fx");
		Mat->SetBlend("AlphaBlend");
	}
}