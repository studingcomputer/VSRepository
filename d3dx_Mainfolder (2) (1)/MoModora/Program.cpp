#include "stdafx.h"
#include "Systems/Device.h"
#include "Scene/Scene.h"
#include "Viewer/Freedom.h"
#include "Scene/MainScene.h"


SceneValues* values;
vector<Scene*> scenes;

void InitScene()
{
	values = new SceneValues();
	values->MainCamera = new Freedom();
	D3DXMatrixIdentity(&values->Projection);

	scenes.push_back(new MainScene(values));
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

*/