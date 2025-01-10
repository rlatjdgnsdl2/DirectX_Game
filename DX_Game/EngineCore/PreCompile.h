#pragma once

#include <EnginePlatform/PreCompile.h>


#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EnginePlatform.lib")

#include <wrl.h>
#include <d3d11_4.h> 
#include <d3dcompiler.h> 


#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI") 

#include "EngineCore.h"

#include "Level.h"
#include "Actor.h"
#include "Pawn.h"
#include "GameMode.h"


#include "ActorComponent.h"
#include "SceneComponent.h"
#include "DefaultSceneComponent.h"

#include "EngineGraphicDevice.h"
#include "RenderUnit.h"
#include "Renderer.h"
#include "SpriteRenderer.h"
#include "Collision.h"
#include "TimeEventComponent.h"

#include "EngineCamera.h"
#include "CameraActor.h"

#include "EngineResources.h"
#include "EngineVertex.h"
#include "EngineTexture.h"
#include "EngineSprite.h"
#include "EngineConstantBuffer.h"
#include "EngineVertexBuffer.h"
#include "EngineDeviceBuffer.h"
#include "EngineDepthStencilState.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayOutInfo.h"
#include "Mesh.h"
#include "EngineMaterial.h"
#include "EngineRasterizerState.h"
#include "EngineSampler.h"
#include "EngineShader.h"
#include "EngineShaderResources.h"

#include "EngineBlend.h"

