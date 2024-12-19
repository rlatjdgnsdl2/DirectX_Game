#include "PreCompile.h"
#include "Renderer.h"
#include <EngineBase/EngineString.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>


URenderer::URenderer()
{
}

URenderer::~URenderer()
{
	VertexBuffer = nullptr;
	VSShaderCodeBlob = nullptr;
	VSErrorCodeBlob = nullptr;

}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();
	UObject::SetOrder(_Order);
	ULevel* Level = GetActor()->GetWorld();
	// std::shared_ptr<URenderer> Render(this);
	// std::enable_shared_from_this<UObject> ��ӹ��� Ŭ������ �ڱ��ڽ��� this
	// std::shared_ptr�� ������� this�� ����ϰ� ������ ȣ���ϴ� �Լ�.
	// std::shared_ptr<UObject> ObjectPtr = UObject::shared_from_this();
	// dynmaic_cast�� ����ϴ� ����� ���� ���̴�. 
	// dynamic_cast <= �� ������ �����͸� ��ȯ��Ű�� �༮���� std::shared_ptr
	// std::shared_ptr<int> NewInt = std::make_shared<int>();
	// std::shared_ptr<URenderer> RendererPtr = std::dynamic_pointer_cast<URenderer>(ObjectPtr);
	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();
	Level->ChangeRenderGroup(PrevOrder, RendererPtr);
}

ENGINEAPI void URenderer::BeginPlay()
{
	SetOrder(0);

	// �⺻���� ������ ������������ ������ ���� 
	// ��� �⺻ �ڵ���� �� �ĺ� �����Դϴ�.

	InputAssembler1Init();
	VertexShaderInit();
	InputAssembler2Init();
	RasterizerInit();
	PixelShaderInit();
}

void URenderer::Render(float _DeltaTime)
{
	InputAssembler1Setting();
	VertexShaderSetting();
	InputAssembler2Setting();
	RasterizerSetting();
	PixelShaderSetting();
	OutPutMergeSetting();
	// �ε��� ���۸� ���ؼ� �׸��ڴ�.
	UEngineCore::Device.GetContext()->DrawIndexed(6, 0, 0);

}



void URenderer::InputAssembler1Init()
{
	// ���ؽ� ���۸� �׷���ī�忡�� ����� �޶�� ��û
	// CPU
	std::vector<EngineVertex> Vertexs;
	Vertexs.resize(4);

	Vertexs[0] = EngineVertex{ FVector(-0.5f, 0.5f, -0.0f), {} };
	Vertexs[1] = EngineVertex{ FVector(0.5f, 0.5f, -0.0f), {} };
	Vertexs[2] = EngineVertex{ FVector(-0.5f, -0.5f, -0.0f), {} };
	Vertexs[3] = EngineVertex{ FVector(0.5f, -0.5f, -0.0f), {} };
	// 0   1
	// 
	// 2   3


	D3D11_BUFFER_DESC BufferInfo = { 0 };

	BufferInfo.ByteWidth = sizeof(EngineVertex) * static_cast<int>(Vertexs.size());
	// �뵵�� ���ؽ� ����
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPU���� �����Ҽ� �־�?
	BufferInfo.CPUAccessFlags = 0;
	// �߿� �޸� ��ġ�� �׷���ī��� �Ұų� cpu�� �Ұž�?
	// �������� �ɼ�

	// D3D11_USAGE_DEFAULT
	// GPU���� �б� �� ���� �׼����� �ʿ��� ���ҽ��Դϴ�.�̴� ���� �Ϲ����� ��� ������ �� �ֽ��ϴ�.

	// D3D11_USAGE_IMMUTABLE
	// GPU������ ���� �� �ִ� ���ҽ��Դϴ�.GPU���� �ۼ��� �� ������ CPU���� ���� �׼����� �� �����ϴ�.�� ������ ���ҽ��� ���� �Ŀ� ������ �� �����Ƿ� ���� �� �ʱ�ȭ�ؾ� �մϴ�.

	// D3D11_USAGE_DYNAMIC
	// GPU(�б� ����)�� CPU(���� ����)���� �׼����� �� �ִ� ���ҽ��Դϴ�.���� ���ҽ��� CPU���� �����Ӵ� �� �� �̻� ������Ʈ�Ǵ� ���ҽ��� �����մϴ�.���� ���ҽ��� ������Ʈ�Ϸ��� Map �޼��带 ����մϴ�.

	// ��Ʈ���� ä���Ҷ�. 
	// 	D3D11_USAGE_STAGING
	// GPU���� CPU���� ������ ����(����)�� �����ϴ� ���ҽ��Դϴ�.

	BufferInfo.Usage = D3D11_USAGE_DEFAULT;


	// �ʱⰪ
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = &Vertexs[0];

	// GPU�� xxx ũ���� ���� ������ּ���� ��� �Ʒ��� �Լ��� ����ϴ�.
	if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, &Data, &VertexBuffer))
	{
		MSGASSERT("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}

	// ��ǲ ���̾ƿ� �̶�� ���� ������ �Ѵ�.
	// ���ؽ� ���̴��� �־�� ��ǲ���̾ƿ� �̶�� ���� ����� �ִ�.
}

void URenderer::InputAssembler1Setting()
{
	UINT VertexSize = sizeof(EngineVertex);
	// �� ���ؽ� ���۰� 10��¥���ε� 3��° ���ؽ� ���� ��������.
	UINT Offset = 0;

	// �ѹ��� �������� ���ؽ� ���۸� �����Ҽ� �ִ�.
	// ���ؽ����������� 1���� �迭�� �־��ִµ�.
	// 0�����Ժ��� 1�� ����ϰڴ�.
	// ���ؽ� �ϳ��� ũ��� VertexSize
	// Offset���� ���ؽ��� ����ϰڴ�.



	ID3D11Buffer* ArrBuffer[1];
	ArrBuffer[0] = VertexBuffer.Get();

	UEngineCore::Device.GetContext()->IASetVertexBuffers(0, 1, ArrBuffer, &VertexSize, &Offset);
	UEngineCore::Device.GetContext()->IASetInputLayout(InputLayOut.Get());
}

void URenderer::InputAssembler1LayOut()
{
	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
	//UINT NumElements,
	//const void* pShaderBytecodeWithInputSignature, <= ���̴� �߰� ������ �ڵ� �־�޶�� �̴ϴ�
	//SIZE_T BytecodeLength,
	//ID3D11InputLayout** ppInputLayout

	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutData;


	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "POSITION";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 0;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

		// �ν��Ͻ��� �����Ҷ� �̾߱� �ϰڽ��ϴ�.
		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "COLOR";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 16;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

		// �ν��Ͻ��� �����Ҷ� �̾߱� �ϰڽ��ϴ�.
		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}



	// ���̴����� � ��ǲ���̾ƿ��� ����ϴ��� �˷���.
	HRESULT Result = UEngineCore::Device.GetDevice()->CreateInputLayout(
		&InputLayOutData[0],
		static_cast<unsigned int>(InputLayOutData.size()),
		VSShaderCodeBlob->GetBufferPointer(),
		VSShaderCodeBlob->GetBufferSize(),
		&InputLayOut);

	if (S_OK != Result)
	{
		MSGASSERT("��ǲ ���̾ƿ� ������ �����߽��ϴ�");
	}

}


void URenderer::VertexShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");


	std::string Path = File.GetPathToString();

	std::wstring WPath = UEngineString::AnsiToUnicode(Path);

	// ���̴� �ڵ带 �׳� ���ڿ��� ���� ������ �Ҽ��� �ִ�.
	//std::string ShaderCode = "struct EngineVertex \	{ \		float4 COLOR : COLOR; \		float4 OSITION : POSITION; \	}; \	struct VertexShaderOutPut \	{ \		float4 SVPOSITION : V_POSITION; \		float4 COLOR : COLOR; \	}; \	VertexShaderOutPut VertexToWorldEngineVertex _Vertex) \	{ \		VertexShaderOutPut OutPut; \		utPut.SVPOSITION = _Vertex.POSITION; \		OutPut.COLOR = _Vertex.COLOR; \
	//	return OutPut; \	} 
	// D3DCompile()

	// ������ �����.
	std::string version = "vs_5_0";

	int Flag0 = 0;
	int Flag1 = 0;

#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif

	// ����� ����ְ� �ɰ��̴�.
	// ���� �������ٰ��ϴ� �ϴµ� �������� �����ϴ�.
	// Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0]
	// [100][100][0][1]

	// [1][0][0][100]
	// [0][1][0][100]
	// [0][0][1][0]
	// [0][0][0][1]

	D3DCompileFromFile(
		WPath.c_str(),
		nullptr, // Define TEST ������ ��ó���⸦ ������.
		nullptr,
		"VertexToWorld",
		version.c_str(),
		Flag0,
		Flag1,
		&VSShaderCodeBlob,
		&VSErrorCodeBlob
	);

	if (nullptr == VSShaderCodeBlob)
	{
		std::string ErrString = reinterpret_cast<char*>(VSErrorCodeBlob->GetBufferPointer());
		MSGASSERT("���̴� �ڵ� �߰����忡�� �����߽��ϴ�\n" + ErrString);
		return;
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreateVertexShader(
		VSShaderCodeBlob->GetBufferPointer(),
		VSShaderCodeBlob->GetBufferSize(),
		nullptr,
		&VertexShader
	);

	if (S_OK != Result)
	{
		MSGASSERT("���ؽ� ���̴� ������ �����߽��ϴ�.");
	}

	InputAssembler1LayOut();
}

void URenderer::VertexShaderSetting()
{
	UEngineCore::Device.GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);
}

void URenderer::RasterizerInit()
{
	D3D11_RASTERIZER_DESC Desc = {};

	// FXAA ���� ���̷�Ʈ�� ���� ����͵��� �� ������.
	// Desc.AntialiasedLineEnable = true;
	// Desc.DepthClipEnable = true;

	// Face�ø� 
	// None�̸� �ð���� �ݽð���� �� ���
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

	// �鿡 ������ ���δ�.
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	// �鿡 ���븸 ���δ�.
	// Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

	UEngineCore::Device.GetDevice()->CreateRasterizerState(&Desc, RasterizerState.GetAddressOf());

	ViewPortInfo.Height = 720.0f;
	ViewPortInfo.Width = 1280.0f;
	ViewPortInfo.TopLeftX = 0.0f;
	ViewPortInfo.TopLeftY = 0.0f;
	ViewPortInfo.MinDepth = 0.0f;
	ViewPortInfo.MaxDepth = 1.0f;
}


void URenderer::RasterizerSetting()
{
	UEngineCore::Device.GetContext()->RSSetViewports(1, &ViewPortInfo);
	UEngineCore::Device.GetContext()->RSSetState(RasterizerState.Get());
}

void URenderer::InputAssembler2Init()
{
	std::vector<unsigned int> Indexs;

	Indexs.push_back(0);
	Indexs.push_back(1);
	Indexs.push_back(2);

	Indexs.push_back(1);
	Indexs.push_back(3);
	Indexs.push_back(2);


	D3D11_BUFFER_DESC BufferInfo = { 0 };
	BufferInfo.ByteWidth = sizeof(unsigned int) * static_cast<int>(Indexs.size());
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = &Indexs[0];
	if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, &Data, &IndexBuffer))
	{
		MSGASSERT("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}
}

void URenderer::InputAssembler2Setting()
{
	int Offset = 0;

	// DXGI_FORMAT_R8_UINT; <= �������� �Ʋ���.
	// DXGI_FORMAT_R16_UINT; <= �������� �Ʋ���.
	UEngineCore::Device.GetContext()->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, Offset);

	UEngineCore::Device.GetContext()->IASetPrimitiveTopology(Topology);
}





void URenderer::PixelShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");


	std::string Path = File.GetPathToString();

	std::wstring WPath = UEngineString::AnsiToUnicode(Path);

	// ������ �����.
	std::string version = "ps_5_0";

	int Flag0 = 0;
	int Flag1 = 0;

#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif

	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	D3DCompileFromFile(
		WPath.c_str(),
		nullptr, // Define TEST ������ ��ó���⸦ ������.
		nullptr,
		"PixelToWorld",
		version.c_str(),
		Flag0,
		Flag1,
		&PSShaderCodeBlob,
		&PSErrorCodeBlob
	);

	if (nullptr == PSShaderCodeBlob)
	{
		std::string ErrString = reinterpret_cast<char*>(PSErrorCodeBlob->GetBufferPointer());
		MSGASSERT("���̴� �ڵ� �߰����忡�� �����߽��ϴ�\n" + ErrString);
		return;
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreatePixelShader(
		PSShaderCodeBlob->GetBufferPointer(),
		PSShaderCodeBlob->GetBufferSize(),
		nullptr,
		&PixelShader
	);

	if (S_OK != Result)
	{
		MSGASSERT("�ȼ� ���̴� ������ �����߽��ϴ�.");
	}
}

void URenderer::PixelShaderSetting()
{
	UEngineCore::Device.GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}

void URenderer::OutPutMergeSetting()
{
	// �迭 �־��ټ� �ִ�. 
	// 0���̸� sv_target0
	ID3D11RenderTargetView* RTV = UEngineCore::Device.GetRTV();

	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
	ArrRtv[0] = RTV; // SV_Target0

	UEngineCore::Device.GetContext()->OMSetRenderTargets(1, &ArrRtv[0], nullptr);
}