#pragma once

#include <Windows.h>

#include <d3d9.h>
#include <d3d11.h>    // DirectX 11使用の為のヘッダ.
#include <d3dx11.h>
#include <d3d11_1.h>
#include <d3dx9math.h>
#include <directxcolors.h>
#include <DirectXMath.h>
#include <D3DX11tex.h>
#include "Header/WICTextureLoader/WICTextureLoader.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

using namespace std;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DX11.lib")
#pragma comment(lib,"winmm.lib")

using namespace DirectX;

constexpr auto WIND_DPI_W = (1280);
constexpr auto WIND_DPI_H = (720);

constexpr auto FPS_60 = (1.f/60.f);

#define SAFE_RELEASE(p)      { if( nullptr != p ) { p->Release(); p = nullptr; } }

template<typename T>
constexpr auto S_TO_MS(T x) { return x*1000.f; }

#include "GameEngine/GameManager/GameManager.h"
#include "GameEngine/GameObject/GameObject.h"
#include "GameEngine/Timer/Timer.h"
#include "GameEngine/Window/Window.h"
#include "GameEngine/Vector/Vector.h"
#include "GameEngine/DirectX11/DirectX11.h"

using namespace GameEngine;
