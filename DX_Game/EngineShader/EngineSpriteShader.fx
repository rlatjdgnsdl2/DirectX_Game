
// #include ""



// ���̴��� ���� �Լ��� ���� ��κ� �ִ����� ������ ȿ����
// ���ÿ� ����ȴ�.

// Vertex[6]

// for
// Vertex[i] * world

// �׷��� ������1
// ���ÿ� �ȴ� => Vertex[0] * world Vertex[0] * world Vertex[0] * world Vertex[0] * world Vertex[0] * world Vertex[0] * world

// ���� ���� ���� ���ǳ��� �ټ� �ֽ��ϴ�.
// HLSL�Դϴ�. ���̴����� C++�� �ƴմϴ�.
// ���⿡ ������ �ڵ�� ���̴� ���� �ľ� �մϴ�.
// Shader 7.0 12
// Shader 5.0 11 <= ������ ����

// ��׳� C++�ε�?
// �ø�ƽ�� �ٿ���� �մϴ�.
// ���� �� ���� �÷�����
// �������̿���

//#define TEST
//#ifdef TEST
//#else
//#endif

struct EngineVertex
{
    float4 COLOR : COLOR;
    float4 POSITION : POSITION;

};

// ���ؽ� ���̴��� ������ ���ϰ��� �־�� �մϴ�.
// ��ǲ�����2�� �ѱ� ���� ����������ϴµ�.
// �̶��� ��Ģ�� �ֽ��ϴ�.

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION;
    float4 COLOR : COLOR;
};

// ���ؽ����̴��� �� �������.
VertexShaderOutPut VertexToWorld(EngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
	// _Vertex 0.5, 0.5
    OutPut.SVPOSITION = _Vertex.POSITION;
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}

float4 PixelToWorld(VertexShaderOutPut _Vertex)
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}