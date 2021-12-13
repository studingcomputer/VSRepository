#include "stdafx.h"
#include "Systems/Device.h"
#include "Scene/Scene.h"
#include "Viewer/Freedom.h"
#include "Scene/Stage1.h"
#include "Scene/Stage2.h"


SceneValues* values;
vector<Scene*> scenes;

int whichScene_Printing = 1;

void InitScene()
{
	values = new SceneValues();
	values->MainCamera = new Freedom();
	D3DXMatrixIdentity(&values->Projection);

	scenes.push_back(new Stage1(values));
	scenes.push_back(new Stage2(values));
}

void DestroyScene()
{
	for (Scene* scene : scenes)
		SAFE_DELETE(scene);
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values);
}


void Update()
{
	values->MainCamera->Update();

	D3DXMatrixOrthoOffCenterLH(&(values->Projection), 0, (float)Width, 0, (float)Height, -1, 1);

	scenes[whichScene_Printing - 1]->Update();

}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 0);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		scenes[whichScene_Printing - 1]->Render();
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
