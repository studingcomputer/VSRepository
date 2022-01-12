#include "stdafx.h"
#include "Systems/Device.h"
#include "Scene/Scene.h"
#include "Viewer/Freedom.h"
#include "Scene/Sonic.h"


SceneValues* values;
vector<Scene*> scenes;

void InitScene()
{
	values = new SceneValues();
	values->MainCamera = new Freedom();
	D3DXMatrixIdentity(&values->Projection);

	scenes.push_back(new Sonic(values));
}

void DestroyScene()
{
	for (Scene* scene : scenes)
		SAFE_DELETE(scene);
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values);
}

//D3DXVECTOR2 horizontal(0, 800), vertical(0, 600);

void Update()
{
	values->MainCamera->Update();

	D3DXMatrixOrthoOffCenterLH(&(values->Projection),
		(float)Width * -0.5f, (float)Width * 0.5f,
		(float)Height * -0.5f, (float)Height * 0.5f, -10, 10);

	//D3DXMatrixOrthoOffCenterLH(&(values->Projection), horizontal.x, horizontal.y, vertical.x, vertical.y, -10, 10);

	for (Scene* scene : scenes)
		scene->Update();

}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 0);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{


		for (Scene* scene : scenes)
			scene->Render();
	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring text = L"";

		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 20;

		text = L"FPS : " + to_wstring((int)ImGui::GetIO().Framerate);

		DirectWrite::RenderText(text, rect);

		rect.top += 20;
		rect.bottom += 20;

		text = L"Camera Pos : ";
		text += to_wstring((int)values->MainCamera->Position().x);
		text += L", ";
		text += to_wstring((int)values->MainCamera->Position().y);
		DirectWrite::RenderText(text, rect);

	}

	DirectWrite::GetDC()->EndDraw();


	SwapChain->Present(0, 0);
}

/*
//idle 0, run 0~5

SetClip(shaderFile, spriteFile, clip, 14, 65, 28, 23, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 60, 64, 25, 24, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 106, 63, 23, 25, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 151, 65, 31, 23, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 196, 63, 33, 25, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 241, 62, 32, 26, clipSpeed4);

//hit 맞았을 때, 하나만 출력. 이후 유효타를 맞을때마다 번갈아가며 출력

SetClip(shaderFile, spriteFile, clip, 14, 113, 24, 28, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 59, 114, 24, 27, clipSpeed4);

//attack

SetClip(shaderFile, spriteFile, clip, 32, 184, 24, 26, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 114, 179, 20, 31, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 180, 184, 46, 24, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 260, 186, 52, 21, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 341, 176, 58, 34, clipSpeed4);//여기부터 유효타, 이 전까진 때리는 거로 캔슬 가능
SetClip(shaderFile, spriteFile, clip, 423, 181, 58, 29, clipSpeed4);
SetClip(shaderFile, spriteFile, clip, 504, 181, 59, 29, clipSpeed4);
*/