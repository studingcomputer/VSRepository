#pragma once

#include <windows.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
using namespace std;

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dX10.h>
#include <d3dx10math.h>
#include <d3dx11effect.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "effects11d.lib")
#pragma comment(lib, "d3dcompiler.lib")

//DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//ImGui
#include <imgui.h>
#include <imguiDx11.h>
#pragma comment(lib, "imgui.lib")

#include "Systems/Keyboard.h"
#include "Systems/Time.h"
#include "Systems/DirectWrite.h"
#include "Systems/CMouse.h"

#include "Renders/Shader.h"
#include "Renders/Rect.h"
#include "Renders/Sprite.h"
#include "Renders/Clip.h"
#include "Renders/Animation.h"

#include "Utilities/Math.h"
#include "Utilities/Path.h"
#include "Utilities/String.h"
#include "Utilities/XML.h"
#include "Utilities/BinaryFile.h"

#define SAFE_RELEASE(p){ if(p){ (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(p){ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p){ if(p){ delete [] (p); (p) = NULL; } }

const wstring Textures = L"../_Textures/";
const wstring Shaders = L"../_Shaders/";

extern UINT Width;
extern UINT Height;

extern HWND Hwnd;
extern wstring Title;

extern IDXGISwapChain* SwapChain;
extern ID3D11Device* Device;
extern ID3D11DeviceContext* DeviceContext;
extern ID3D11RenderTargetView* RTV;

extern Keyboard* Key;
extern CMouse* Mouse;
extern Time* Timer;

enum class PlayerAct
{
	Nothing = 1,
	MovingRight,
	MovingLeft,
	Turning,
	Breaking,
	Rising,
	Falling,
	Crouching,
	Rolling,
	Jumping,
	LandHard,
	LandSoft,
	Attack1,
	Attack2,
	Attack3,
	AirAttack_jumping,
	AirAttack_falling,
	Attack_Bow,
	Attack_Bow_Crouching,
	Attack_Bow_Falling
	//나중에 추가예정
};

/*

에디터 요점

맵(배경) 마음대로 바꿀 수 있어야함							  - scene가 하나로 통일(completed),			배경 이미지만 바꾸는 작업 필요(completed).																										*플레이어가 건드릴 수 있는 부분은 Imgui에 넣음.
몬스터의 종류, 개수, 위치를 마음대로 정할 수 있어야함.	      - 처음에 모든 실행을 멈추고(completed),		벡터에 몬스터 데이터를 넣는 작업 필요.												몬스터의 위치가 마우스포인터를 따라다녀야함.					*플레이어가 건드릴 수 있는 부분은 Imgui에 넣음.
플레이어의 시작위치도 정할 수 있어야함.						  - 처음에 모든 실행을 멈추고(completed),		플레이어의 포지션을 버튼 클릭 시 마우스포인터를 따라다니게 하고,						마우스 클릭 시 그 자리에 고정시켜야함.							*플레이어가 건드릴 수 있는 부분은 Imgui에 넣음.
발판을 만들어, 플레이에 변수를 주는 부분또한 만들 수 있어야함. - 처음에 모든 실행을 멈추고(completed),	    벡터에 바닥 객체를 집어넣는 작업 필요.												확정시까지 마우스포인터를 따라다녀야함.							*플레이어가 건드릴 수 있는 부분은 Imgui에 넣음.

*/
