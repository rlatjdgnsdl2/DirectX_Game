struct EngineVertex
{
	float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
	float4 COLOR : COLOR;
};



struct VertexShaderOutPut
{
	float4 SVPOSITION : SV_POSITION; 
    float4 TEXCOORD : TEXCOORD;
	float4 COLOR : COLOR;
};

// 상수버퍼를 사용하겠다.
cbuffer FTransform : register(b0)
{
	float4 Scale;
	float4 Rotation;
	float4 Qut;
	float4 Location;

	// 릴리에티브 로컬
	float4 RelativeScale;
	float4 RelativeRotation;
	float4 RelativeQut;
	float4 RelativeLocation;

	// 월드
	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldQuat;
	float4 WorldLocation;

	float4x4 ScaleMat;
	float4x4 RotationMat;
	float4x4 LocationMat;
	float4x4 RevolveMat;
	float4x4 ParentMat;
	float4x4 LocalWorld;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4x4 WVP;
};

// 상수버퍼는 아무것도 세팅해주지 않으면 기본값이 0으로 채워집니다.
cbuffer FSpriteData : register(b1)
{
	float4 CuttingPos;
	float4 CuttingSize;
	float4 Pivot; // 0.5 0.0f
};



// 버텍스쉐이더를 다 만들었다.
VertexShaderOutPut CollisionDebug_VS(EngineVertex _Vertex)
{
	VertexShaderOutPut OutPut;
	_Vertex.POSITION.x += (1.0f - Pivot.x) - 0.5f;
	_Vertex.POSITION.y += (1.0f - Pivot.y) - 0.5f;
	
	OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
    OutPut.TEXCOORD = _Vertex.TEXCOORD;
	OutPut.COLOR = _Vertex.COLOR;
	return OutPut;
}




cbuffer ResultColor : register(b0)
{
	float4 OutColor;

};

// 이미지를 샘플링해서 이미지를 보이게 만들고
float4 CollisionPixel_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
    float4 UV = _Vertex.TEXCOORD;
    float4 Color = OutColor;
	
    float BorderThickness = 0.0f;
    float IsBorder = step(UV.x, BorderThickness) + step(UV.y, BorderThickness) + step(1.0f - UV.x, BorderThickness) + step(1.0f - UV.y, BorderThickness);
    if (IsBorder > 0.0f)
    {
        return Color;
    }
    return float4(0.0f, 0.0f, 0.0f, 0.0f);
};
