#include "PreCompile.h"
#include "EngineGraphicDevice.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
}

void UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
    // �̰� ���ؼ� ���� �ִ� �׷���ī�忡 �޸𸮰� �����ϴ�.
    IDXGIFactory* Factory = nullptr;
    IDXGIAdapter* Adapter = nullptr;


    // Factory�� ���̷�Ʈ x���� �����ϴ� �׷���ī�� �޸𸮿� ������ ������ִ� �������̽� �Դϴ�.
    // #pragma comment(lib, "dxguid")
    // ���̷�Ʈx�� ���� ���̺귯������ Ŭ������ �����ϴ°� �ƴϰ�
    // GUID��� ������ �ڵ� ����� �׶��׶����� �ε��ϴ� ����� ���ϴµ�.

    //MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369") => GUID��� �Ѵ�.
    //   IDXGIFactory : public IDXGIObject


    HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

    if (nullptr == Factory)
    {
        MSGASSERT("�׷���ī�� ����� ���丮 ������ �����߽��ϴ�.");
        return;
    }

    for (int Index = 0;; ++Index)
    {
        IDXGIAdapter* CurAdapter = nullptr;

        Factory->EnumAdapters(Index, &CurAdapter);

        if (nullptr == CurAdapter)
        {
            break;
        }

        Adapter = CurAdapter;
    }

    if (nullptr != Factory)
    {
        Factory->Release();
    }

    if (nullptr == Adapter)
    {
        MSGASSERT("�׷���ī�尡 �޷����� ���� ��ǻ���Դϴ�.");
        return;
    }


    Adapter->Release();
}

void UEngineGraphicDevice::CreateDeviceAndContext()
{
    // ����̽��� �������
    // ����̽� �������� ������� �մϴ�.
    // ����̽��� ��带 ������� �մϴ�


    //IDXGIAdapter* pAdapter,
    // �׷������� ��������� �˷��ּ���.
    // nullptr �־��ָ� �˾Ƽ� ã��.
    // �׷���ī�� 2�� �޷��ִ� ������� �ִ�.


    //D3D_DRIVER_TYPE DriverType,
    //HMODULE Software,
    //UINT Flags,
    //_In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    //UINT FeatureLevels,
    //UINT SDKVersion,
    //_COM_Outptr_opt_ ID3D11Device** ppDevice,
    //_Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    //_COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext

    GetHighPerFormanceAdapter();

#ifdef _DEBUG
#endif

    // D3D11CreateDevice();

}

void UEngineGraphicDevice::CreateBackBuffer(const UEngineWindow& _Window)
{
    int a = 0;
}