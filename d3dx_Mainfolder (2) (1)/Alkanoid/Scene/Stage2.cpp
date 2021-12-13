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

	backGround = new Sprite(Textures + L"Stage2.png", shaderFile, 192, 0, 192*2, 232);
	backGround->Position(400, 350);
	backGround->Scale(3.5f, 3.5f);


	player = new Player(D3DXVECTOR2(130, 100), D3DXVECTOR2(2.5f, 2.5f));
	bullet = new Bullet(Shaders + L"009_Sprite.fx", D3DXVECTOR2(300, 300), 0, 0);
	fire = new Fire(Shaders + L"009_Sprite.fx", D3DXVECTOR2(300, 100));
}

Stage2::~Stage2()
{
	SAFE_DELETE(fire);
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);

	SAFE_DELETE(backGround);
}

void Stage2::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	player->Update(V, P);
	bullet->Update(V, P);
	fire->Update(V, P);
}

void Stage2::Render()
{
	RenderBackground();

	static bool check = false;

	Sprite* a = bullet->GetClip()->GetSprite();
	Sprite* b = fire->GetClip()->GetSprite();

	check = Sprite::OBB(a, b);

	a->DrawCollision(check);
	b->DrawCollision(check);





	player->Render();
	bullet->Render();
	fire->Render();
}

void Stage2::RenderBackground()
{
	backGround->Render();
}