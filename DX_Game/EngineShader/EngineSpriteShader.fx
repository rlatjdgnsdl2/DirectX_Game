struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

// ���ؽ� ���̴��� ������ ���ϰ��� �־�� �մϴ�.
// ��ǲ�����2�� �ѱ� ���� ����������ϴµ�.
// �̶��� ��Ģ�� �ֽ��ϴ�.

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // ����Ʈ����� �������� �������Դϴ�.
    float4 UV : TEXCOORD; // 
    float4 COLOR : COLOR;
};

// ������۸� ����ϰڴ�.
cbuffer FTransform : register(b0)
{
	// transformupdate�� 
	// �Ʒ��� ������ �� �����ؼ�
	// WVP�� ������ �Լ��̴�.
	// ��ȯ�� ����
    float4 Scale;
    float4 Rotation;
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
};

// ���ؽ����̴��� �� �������.
VertexShaderOutPut VertexToWorld(EngineVertex _Vertex)
{
	// CPU���� ����� ���� ���̴����� �ѱ�� ����� �˾ƾ� �ϴµ�
	// ������۶�� �θ��ϴ�.
	// ���߿��� ���� �⺻���� ���� ������۸� 
	
	// float4x4 WVP;
	
    VertexShaderOutPut OutPut;
	// _Vertex 0.5, 0.5
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	
	// 00 10 => 0.3 0.3  0.7 0.3
	// 01 11 => 0.3 0.7  0.7 0.7
	
	// CuttingPos 0.3 0.3
	// CuttingSize 0.4 0.4 
	
    OutPut.UV.x = (_Vertex.UV.x * CuttingSize.x) + CuttingPos.x;
    OutPut.UV.y = (_Vertex.UV.y * CuttingSize.y) + CuttingPos.y;
	
	
	
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}

// �ؽ�ó 1��� 
Texture2D ImageTexture : register(t0);
// ���÷� 1���� �ʿ��մϴ�.
SamplerState ImageSampler : register(s0);

// �̹����� ���ø��ؼ� �̹����� ���̰� �����
float4 PixelToWorld(VertexShaderOutPut _Vertex) : SV_Target0
{
	
	// ImageTexture.Load({0,0));
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
    return Color;
}