#include "stdafx.h"
#include "Stage1.h"
#include "Objects/Player.h"
#include "Viewer/Following.h"
#include "Viewer/Freedom.h"

Stage1::Stage1(SceneValues * values)
	: Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"Arkanoid/Fields.png", shaderFile, 0, 0, 192, 232);//화면비율 192:232 = 96:116 = 48:58 = 24:29 끝
	backGround->Scale(3.5f, 3.5f);//전체 3.5배 했으니, 비율도 3.5	배로 늘어나야함. = 672:812
	backGround->Position(0, 0);
	//D3DXVECTOR2(0, -356)
	player = new Player(D3DXVECTOR2(0, -356), D3DXVECTOR2(2.5f, 2.5f));

	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Freedom();
}

Stage1::~Stage1()
{
	SAFE_DELETE(player);

	SAFE_DELETE(backGround);
}

void Stage1::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	player->Update(V, P);
}

void Stage1::Render()
{
	backGround->Render();

	player->Render();

	string scoreString = "x = " + to_string(player->GetSprite()->Position().x);
	scoreString += " y = " + to_string(player->GetSprite()->Position().y);

	ImGui::Text(scoreString.c_str());

}