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



// ���ؽ����̴��� �� �������.
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

// �̹����� ���ø��ؼ� �̹����� ���̰� �����
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
