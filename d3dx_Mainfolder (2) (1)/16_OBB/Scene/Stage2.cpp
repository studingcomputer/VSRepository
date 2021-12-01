#include "stdafx.h"
#include "Stage2.h"
#include "Objects/Player.h"
#include "Viewer/Following.h"
#include "Objects/Bullet.h"
#include "Objects/Fire.h"


Stage2::Stage2(SceneValues * values)
	: Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGrounds[0] = new Sprite(Textures + L"Stage2.png", shaderFile, 26, 311, 613, 503);
	backGrounds[0]->Position(400, 350);
	backGrounds[0]->Scale(1.2f, 2.6f);

	backGrounds[1] = new Sprite(Textures + L"Stage2.png", shaderFile, 13, 11, 714, 215);
	backGrounds[1]->Position(400, 350);
	backGrounds[1]->Scale(1.2f, 2.6f);

	backGrounds[2] = new Sprite(Textures + L"Stage2.png", shaderFile, 13, 242, 894, 279);
	backGrounds[2]->Position(400, 40);
	backGrounds[2]->Scale(1.2f, 2.6f);


	player = new Player(D3DXVECTOR2(130, 100), D3DXVECTOR2(2.5f, 2.5f));
	bullet = new Bullet(Shaders + L"009_Sprite.fx", D3DXVECTOR2(300, 300), 0, 0);
	fire = new Fire(Shaders + L"009_Sprite.fx", D3DXVECTOR2(300, 100));
}

Stage2::~Stage2()
{
	SAFE_DELETE(fire);
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);

	SAFE_DELETE(backGrounds[0]);
	SAFE_DELETE(backGrounds[1]);
	SAFE_DELETE(backGrounds[2]);
}

void Stage2::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	backGrounds[0]->Update(V, P);
	backGrounds[1]->Update(V, P);
	backGrounds[2]->Update(V, P);

	player->Update(V, P);
	bullet->Update(V, P);
	fire->Update(V, P);
}

void Stage2::Render()
{
	RenderBackground();

	static bool check = false;

	Sprite* a = player->GetSprite();
	check = Sprite::AABB(a, bullet->Position());

	ImGui::LabelText("AABB", "%d", check ? 1 : 0);


	static bool check2 = false;
	Sprite* b = fire->GetClip()->GetSprite();

	check2 = a->AABB(b);
	ImGui::LabelText("AABB Rectr", "%d", check2 ? 1 : 0);



	player->Render();
	bullet->Render();
	fire->Render();
}

void Stage2::RenderBackground()
{
	backGrounds[0]->Render();
	backGrounds[1]->Render();
	backGrounds[2]->Render();
}