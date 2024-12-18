#include "PreCompile.h"
#include "EngineGraphicDevice.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
	Release();
}
void UEngineGraphicDevice::Release()
{
	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Context = nullptr;
	}
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* ResultAdapter = nullptr;
	unsigned __int64 MaxVideoMemory = 0;

	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MSGASSERT("�׷���ī�� ����� ���丮 ������ �����߽��ϴ�.");
		return nullptr;
	}

	for (int Index = 0;; ++Index)
	{
		IDXGIAdapter* CurAdapter = nullptr;
		Factory->EnumAdapters(Index, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (MaxVideoMemory <= Desc.DedicatedVideoMemory)
		{
			MaxVideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != ResultAdapter)
			{
				ResultAdapter->Release();
			}
			ResultAdapter = CurAdapter;
			continue;
		}
		CurAdapter->Release();
	}

	if (nullptr != Factory)
	{
		Factory->Release();
	}

	if (nullptr == ResultAdapter)
	{
		MSGASSERT("�׷���ī�尡 �޷����� ���� ��ǻ���Դϴ�.");
		return nullptr;
	}
	return ResultAdapter;
}



void UEngineGraphicDevice::CreateDeviceAndContext()
{
	IDXGIAdapter* Adapter = GetHighPerFormanceAdapter();
	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL ResultLevel;
	HRESULT Result = D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&ResultLevel,
		&Context);
	if (nullptr == Device)
	{
		MSGASSERT("�׷��� ����̽� ������ �����߽��ϴ�.");
		return;
	}

	if (nullptr == Context)
	{
		MSGASSERT("�׷��� ���ؽ�Ʈ ������ �����߽��ϴ�.");
		return;
	}
	if (Result != S_OK)
	{
		MSGASSERT("�׷��� ����̽� ������ �����߽��ϴ�.");
		return;
	}
	if (ResultLevel != D3D_FEATURE_LEVEL_11_0 && 
		ResultLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MSGASSERT("���̷�Ʈ 11������ �������� �ʴ� �׷���ī���Դϴ�.");
		return;
	}

	Result = CoInitializeEx(nullptr,COINITBASE_MULTITHREADED);
	if (Result != S_OK)
	{
		MSGASSERT("������ ������ ���뿡 ������ ������ϴ�.");
		return;
	}
	Adapter->Release();
}

void UEngineGraphicDevice::CreateBackBuffer(const UEngineWindow& _Window)
{
	FVector Size = _Window.GetWindowSize();
	DXGI_SWAP_CHAIN_DESC SwapChainInfo = { 0 };
	SwapChainInfo.BufferCount = 2;
	SwapChainInfo.BufferDesc.Width = Size.iX();
	SwapChainInfo.BufferDesc.Height = Size.iY();
	SwapChainInfo.OutputWindow = _Window.GetWindowHandle();
	SwapChainInfo.Windowed = true;
	SwapChainInfo.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainInfo.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;	
	SwapChainInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	SwapChainInfo.SampleDesc.Quality = 0;
	SwapChainInfo.SampleDesc.Count = 1;
	SwapChainInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;



	
}