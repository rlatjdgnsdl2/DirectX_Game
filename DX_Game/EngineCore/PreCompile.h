#pragma once

#include <EnginePlatform/PreCompile.h>

#include "EngineCore.h"
#include "Actor.h"
#include "Pawn.h"
#include "GameMode.h"

#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EnginePlatform.lib")

#include <wrl.h>
#include <d3d11_4.h> // directx 11 ����4�� ���
#include <d3dcompiler.h> // ���̴� �����Ϸ��� �������̽� ���̴��� ���� ����
#include <EnginePlatform/EngineWindow.h>

// ���̺귯����
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

// GetHighPerFormanceAdapter ����� ���ؼ��� ����� ������ �׷���ī�� ������ ���;��ϴµ�
// �̳༮�� �� �Լ����� ������ �ִ�.
#pragma comment(lib, "DXGI") 
