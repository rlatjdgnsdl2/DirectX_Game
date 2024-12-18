#include "PreCompile.h"
#include "Renderer.h"
#include "EngineCore.h"
URenderer::URenderer()
{
}

URenderer::~URenderer()
{
	VertexBuffer->Release();
}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();
	// 100���� �Ǿ���?
	UObject::SetOrder(_Order);

	ULevel* Level = GetActor()->GetWorld();
	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();

	Level->ChangeRenderGroup(PrevOrder, RendererPtr);
}

ENGINEAPI void URenderer::BeginPlay()
{
	SetOrder(0);
	InitInputAssembler1();
}

void URenderer::Render(float _DeltaTime)
{
	// ������ ����������
	SetInputAssembler1();

}

void URenderer::InitInputAssembler1()
{
	std::vector<EngineVertex> Vertexs;
	Vertexs.resize(6);
	Vertexs[0] = EngineVertex{ FVector(-0.5f, 0.5f, -0.5f), {} };
	Vertexs[1] = EngineVertex{ FVector(0.5f, 0.5f, -0.5f), {} };
	Vertexs[2] = EngineVertex{ FVector(-0.5f, -0.5f, -0.5f), {} };
	Vertexs[3] = EngineVertex{ FVector(0.5f, 0.5f, -0.5f), {} };
	Vertexs[4] = EngineVertex{ FVector(0.5f, -0.5f, -0.5f), {} };
	Vertexs[5] = EngineVertex{ FVector(-0.5f, -0.5f, -0.5f), {} };

	D3D11_BUFFER_DESC BufferInfo = { 0 };

	BufferInfo.ByteWidth = sizeof(EngineVertex) * Vertexs.size();

	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	BufferInfo.CPUAccessFlags = 0;

	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = &Vertexs[0];

	if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, &Data, &VertexBuffer))
	{
		MSGASSERT("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}
}

void URenderer::SetInputAssembler1()
{

}
