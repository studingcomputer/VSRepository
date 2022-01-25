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

맵(배경) 마음대로 바꿀 수 있어야함							  - scene가 하나로 통일(completed),			배경 이미지만 바꾸는 작업 필요.																												플레이어가 건드릴 수 있는 부분은 Imgui에 넣음.
몬스터의 종류, 개수, 위치를 마음대로 정할 수 있어야함.	      - 처음에 모든 실행을 멈추고,				벡터에 몬스터 데이터를 넣는 작업 필요.												몬스터의 위치가 마우스포인터를 따라다녀야함.					플레이어가 건드릴 수 있는 부분은 Imgui에 넣음.
플레이어의 시작위치도 정할 수 있어야함.						  - 처음에 모든 실행을 멈추고,				플레이어의 포지션을 버튼 클릭 시 마우스포인터를 따라다니게 하고,						마우스 클릭 시 그 자리에 고정시켜야함.							플레이어가 건드릴 수 있는 부분은 Imgui에 넣음.
발판을 만들어, 플레이에 변수를 주는 부분또한 만들 수 있어야함. - 처음에 모든 실행을 멈추고,			    벡터에 바닥 객체를 집어넣는 작업 필요.												확정시까지 마우스포인터를 따라다녀야함.							플레이어가 건드릴 수 있는 부분은 Imgui에 넣음.

*/

/*

"으억.."
"크윽, 으으.."

용사파티의 대부분은 이미 쓰러졌다.
아마, 내가 어떻게든 힐을 해 봐도 모자랄 듯 보였다.

"..."

말을.. 하지 못했다고는 말하기 어려울 것이다.
그때의 나에겐 분명, 말할 힘은 남아 있었다.
하지만 내 감정이 그걸 막고 있었다.

-치이이

말로는 설명할 수 없는 감정이 내 머릿속에 퍼져나가고 있었다.
조금씩 조금씩 갉아먹으며, 흘러내리고 있었다.
내 정신력은 그리 약하지 않았을 터.
..그렇지만 이런 경우는 상상도 못했던 것이다.

"히힛..?"

칠흑색의 머리카락과, 끝이 보이지 않는 심연을 바라보는 듯한 눈동자.
그와는 대비되는 새하얀 피부와 아름다운 옷.
마치, 백색의 깔끔한 종이에 잉크를 부어버린 듯한, 그런 느낌이었다.

"..망할."

그녀는, 용사파티의 일원.
교단이 숭배하는 존재.
나는 몰랐었지만 날 좋아했었던 한 여자아이.

성녀 아스트레아.

"특별히 용사님만, 여신님 부하로 들어올 수 있도록 해 드릴게요."
"뭐?"

그것 참 형편 좋은 얘기다, 라고 농담을 하기엔 뒤에 있는 동료들이 너무 비참해질 것 같았다.

"젠장."

날 이렇게까지 편애하는 걸 보니 그녀 안의 자신은 살아있는 것 같아, 그나마 안심했다.
하지만 그렇다는 게 지금 상황을 만회시켜주지는 않는다.

그럼에도 불구하고.
난 이전에 약속한 적이 있단 말이다.
만약 여신을 처치하고 모든 일이 다 제대로 돌아가게 된다면.
지구라는 평화로운 세계로 보내주겠다는 약속을 전 마왕 녀석에게 걸어놓았단 말이다.

아직 굴복하지 않아.
그때까지 무엇이든 할 거야.
날 희생해서라도 모두를 보낼 거야.

"..아니, 그쪽 편에는 붙지 않-"

구체화된 흑마법이 내 목을 감쌌다.
그대로, 몸이 공중에 붕 떴다.

"'응'이란 단어가 나오기 전까지는 절대 놔 드리지 않아요."
"컥, 쿨럭.."

필사적으로 다른 방법을 찾아보았다.
나답지 않게 그 방법을 실현시키려 노력하기도 했다.
몇몇개는 가능성을 보여서 모두가 행복한 마무리를 지을 수 있겠다는 희망도 생겼었다. 
그러나.

..이젠 다른 방법이 없다.




-털썩

소라의 몸이, 바닥에 풀썩 쓰러졌다.
아스트레아가 흑마법을 놓은 것이다.
그와 동시에, 아스트레아에게서 하얀 빛이 소라의 몸 쪽으로 새어나가고 있었다.

"무, 무슨?"

그녀가 당황하는 것도 지금 이해할 수 있다.
이건 나의 마지막 보루로 남겨놓고 있었다.

여신의 존재가 알려졌을 때 마왕이 나에게 준 최소한의 장치, '시스템'.
그 안에는, 이런 스킬이 하나 있었다.

[강림]
당신은 당신이 이전에도 계속 원해왔던 '검신'이 되어 이 현실에 '도현'의 몸으로서 강림하게 됩니다.
또한 당신이 빙의하고 있던 육체의 영혼 또한 자신의 주인을 찾아 돌아가게 됩니다.
지속시간은 10분입니다.
하지만, 다음 스킬을 사용 시 지속시간이 초과되면 당신의 영혼은 [복구 불가]상태가 되며, 육체 또한 사라지게 됩니다.

자살 스킬이다.
이런 건, 쓰지 말라고 여러 명에게 들었었다.

하지만, 저기 누워있는 모두를 위해서라도.
다쳐있는 모두를 위해서라도.
난.

"[시스템▷강림]"

저들을 지킬 필요가 있을 것이다.

"뭐야, 어떻게?"

순간, 여신의 목소리가 또렷히 들려왔다.
난 그곳을 향해 칼을 내찔렀다.

-파앗

장막이 들춰지며, 그 안에 있던 모든 것들이 드러나기 시작했다.
아스트레아가 막아보려 했지만, 이미 그녀가 막기엔 내 힘은 이전과는 확연히 달라져 있었다.

"으아아아아악!"

-챙그랑

겹겹이 쌓여있던 보호막이.

-파지직

하나, 하나.

-콰직

전부 사라질때까지.

-지지직

난 베고 또 베었다.

-쌔앵
-콰악

"크읏..! 용케도!"

날 마주하자마자 면전에 흑마력을 들이미는 사람이라니.
이거 예의가 없구만.

-솨아아

날카로운 칼날과 둘러쌓인 신성력에, 그녀의 흑마력은 산산조각났다.

"흐익!"

그와 동시에 힘을 뒤로 돌려 칼날이 뒤로 가게 만든 뒤, 다시 오른팔에 힘을 주어 칼날을 위로 끌어올린다.

"흐압!"

중력의 영향을 배로 받을 때 쯤, 전력으로 내려찍는다.

-콰직
-콰아아

그녀가 있던 자리의 모든 것이 파괴되어, 흔적도 없이 사라져버렸다.
연계기술 [시스템▷강공격]이다.



*/