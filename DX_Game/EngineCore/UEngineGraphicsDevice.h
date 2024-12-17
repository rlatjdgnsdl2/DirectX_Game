#pragma once
#include <d3d11_4.h>
#include<d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")


//	Ό³Έν:
class UEngineGraphicsDevice
{
public:
	UEngineGraphicsDevice();
	virtual ~UEngineGraphicsDevice();
	UEngineGraphicsDevice(const UEngineGraphicsDevice& _Other) = delete;
	UEngineGraphicsDevice(UEngineGraphicsDevice&& _Other) noexcept = delete;
	UEngineGraphicsDevice& operator=(const UEngineGraphicsDevice& _Other) = delete;
	UEngineGraphicsDevice& operator=(UEngineGraphicsDevice&& _Other) noexcept = delete;

protected:

private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;

};

