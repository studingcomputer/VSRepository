#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"


Player* player;

Camera* camera;
Background* bg;
Sprite* sprite;

void InitScene()
{
	player = new Player(D3DXVECTOR2(500, 140), D3DXVECTOR2(2.5f, 2.5f));
	camera = new Following(player);
	//camera = new Freedom;

	bg = new Background(Shaders + L"009_Sprite.fx");

	sprite = new Sprite(Textures + L"Stage.png", Shaders + L"009_Sprite.fx");
	sprite->Scale(2.5f, 2.5f);
	sprite->Position(0, 300);
}

void DestroyScene()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(sprite);
	SAFE_DELETE(player);
	SAFE_DELETE(bg);
}


void Update()
{


	//Projection
	D3DXMATRIX P;
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	camera->Update();

	D3DXMATRIX V = camera->View();

	//bg->Update(V, P);
	player->Update(V, P);
	sprite->Update(V, P);

}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 0);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::LabelText("FPS", "%.0f", ImGui::GetIO().Framerate);


		sprite->Render();
		//bg->Render();
		player->Render();

	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring text = L"반드시 에러를 잡아야 한다 아니면.....";

		RECT rect;
		rect.left = 20;
		rect.top = 20;
		rect.right = 1000;
		rect.bottom = 40;

		DirectWrite::RenderText(text, rect);

		text = L"이름, 凸, ★, SeoulGameAcademy";
		rect.top += 30;
		rect.bottom += 30;

		DirectWrite::RenderText(text, rect);

	}

	DirectWrite::GetDC()->EndDraw();


	SwapChain->Present(0, 0);
}
