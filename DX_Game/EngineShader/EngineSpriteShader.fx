struct EngineVertex
{
	float4 POSITION : POSITION;
	float4 COLOR : COLOR;
};

struct VertexShaderOutPut
{
	float4 SVPOSITION : SV_POSITION;
	float4 COLOR : COLOR;
};

// 버텍스쉐이더를 다 만들었다.
VertexShaderOutPut VertexToWorld(EngineVertex _Vertex)
{
	VertexShaderOutPut OutPut;
	// _Vertex 0.5, 0.5
	OutPut.SVPOSITION = _Vertex.POSITION;
	OutPut.COLOR = _Vertex.COLOR;
	return OutPut;
}

float4 PixelToWorld(VertexShaderOutPut _Vertex) : SV_Target0
{
    
    return _Vertex.COLOR;
  
}