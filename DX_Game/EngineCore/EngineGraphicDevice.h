#pragma once
// 기본적으로 지원해주기 때문
// windowsdk에 포함되어 있고 windowsdk 폴더는 여러분들 설정중 디렉토리에 자동포함되어 있습니다.

#include <d3d11_4.h> // directx 11 버전4용 헤더
#include <d3dcompiler.h> // 쉐이더 컴파일러용 인터페이스 쉐이더는 추후 설명
#include <EnginePlatform/EngineWindow.h>

// 라이브러리들
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

// GetHighPerFormanceAdapter 등등을 위해서는 모니터 정보나 그래픽카드 정보를 얻어와야하는데
// 이녀석이 그 함수들을 가지고 있다.
#pragma comment(lib, "DXGI") 


// 내일 4시 전까지 
// 첫번째 목표 블루스크린(단색스크린)
// 다이렉트 x기반으로한 구조를 완성하면 
// 다이렉트 x에서 무슨색깔로 다 지운다음에 그릴건지를 알려달라고 합니다. 


// 진짜 멀티플랫폼이 되려면
// 여기에는 directx가 뭐하나라도 보이면 안되게 짜야 합니다.

// 설명 :
class UEngineGraphicDevice
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineGraphicDevice();
	ENGINEAPI ~UEngineGraphicDevice();

	// delete Function
	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	void Release();

	void CreateDeviceAndContext();

	void CreateBackBuffer(const UEngineWindow& _Window);

	IDXGIAdapter* GetHighPerFormanceAdapter();

protected:

private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
};

