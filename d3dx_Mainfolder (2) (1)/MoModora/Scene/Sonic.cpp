#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Renders/Line.h"
#include "Viewer/Following.h"

Sonic::Sonic(SceneValues * values)
	:Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";


	backGround = new Sprite(Textures + L"Momodora/groundmap.png", shaderFile);
	backGround->Scale(1.05f, 1.05f);
	backGround->Position(backGround->TextureSize().x * 0.5f - Width * 0.5f, 0.0f);
	lines.push_back(new Line(shaderFile, D3DXVECTOR2((backGround->Position().x) - (backGround->TextureSize().x * 0.5f), -(Height * 0.35f)), D3DXVECTOR2((backGround->Position().x) + (backGround->TextureSize().x * 0.5f), -(Height * 0.35f))));

	player = new Player(D3DXVECTOR2(-50, 100), D3DXVECTOR2(2.5f, 2.5f), backGround);

	values->MainCamera = new Following(player);
}

Sonic::~Sonic()
{
	SAFE_DELETE(backGround);
	for (Line* l : lines)
		SAFE_DELETE(l);
	SAFE_DELETE(player);
	
}


void Sonic::Update()
{
	values->MainCamera->Update();
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	backGround->Update(values->MainCamera->View(), P);

	D3DXVECTOR2 mouse = Mouse->Position();
	D3DXVECTOR2 camera = values->MainCamera->Position();
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;

	mPos = mouse + camera;


	

	for (Line* l : lines)
	{
		l->Update(values->MainCamera->View(), P);
	}

	CheckLines();
	
	player->Update(values->MainCamera->View(), P);
}

void Sonic::Render()
{
	ImGui::LabelText("Position", "%.0f, %.0f", mPos.x, mPos.y);
	ImGui::LabelText("P_Position", "%.2f, %.2f", player->GetSprite()->Position().x, player->GetSprite()->Position().y);
	ImGui::LabelText("P_OnGround", "%s", player->RtOng() ? "true" : "false");
	ImGui::LabelText("P_Status", "%d", (PlayerAct)player->RtStatus());

	backGround->Render();
	player->Render();
	for (Line* l : lines)
	{
		l->Render();
	}

}

void Sonic::CheckLines()
{
	vector<Line*> database;
	Line* main = nullptr;

	for (Line* l : lines)
	{
		int val = player->CheckCollapse_justforfloor(l);
		if (val == 1)
			database.push_back(l);
		else if (val == 2)
			main = l;
	}
	if (main != nullptr)
		player->CheckCollapse_justforfloor(main);
	else
		for (Line* l : database)
			player->CheckCollapse_justforfloor(l);
}
