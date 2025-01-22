struct EngineVertex
{
	float4 POSITION : POSITION;
	float4 UV : TEXCOORD;
	float4 COLOR : COLOR;
};



struct VertexShaderOutPut
{
	float4 SVPOSITION : SV_POSITION; 
	float4 UV : TEXCOORD;  
	float4 COLOR : COLOR;
};

// ������۸� ����ϰڴ�.
cbuffer FTransform : register(b0)
{
	float4 Scale;
	float4 Rotation;
	float4 Qut;
	float4 Location;

	// ������Ƽ�� ����
	float4 RelativeScale;
	float4 RelativeRotation;
	float4 RelativeQut;
	float4 RelativeLocation;

	// ����
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

// ������۴� �ƹ��͵� ���������� ������ �⺻���� 0���� ä�����ϴ�.
cbuffer FSpriteData : register(b1)
{
	float4 CuttingPos;
	float4 CuttingSize;
	float4 Pivot; // 0.5 0.0f
};

cbuffer FUVValue : register(b2)
{
	float4 PlusUVValue;
};

// ���ؽ����̴��� �� �������.
VertexShaderOutPut CollisionDebug_VS(EngineVertex _Vertex)
{
	
	
	VertexShaderOutPut OutPut;
	
	
	_Vertex.POSITION.x += (1.0f - Pivot.x) - 0.5f;
	_Vertex.POSITION.y += (1.0f - Pivot.y) - 0.5f;
	
	OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	OutPut.UV = _Vertex.UV;
	OutPut.COLOR = _Vertex.COLOR;
	return OutPut;
}


Texture2D ImageTexture : register(t0);
// ���÷� 1���� �ʿ��մϴ�.
SamplerState ImageSampler : register(s0);


cbuffer ResultColor : register(b0)
{
	float4 PlusColor;
	float4 MulColor;
};

// �̹����� ���ø��ؼ� �̹����� ���̰� �����
float4 CollisionPixel_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
	float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
	
	if (0.0f >= Color.a)
	{
		clip(-1);
	}
	
    return Color;
};
