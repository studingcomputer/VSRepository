#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Renders/Line.h"

Sonic::Sonic(SceneValues * values)
	:Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	player = new Player(D3DXVECTOR2(-50, 100), D3DXVECTOR2(2.0f, 2.0f));

	backGround = new Sprite(Textures + L"Stage3.png", shaderFile);
	backGround->Position(0, 0);
	((Freedom*)(values->MainCamera))->Position(0, 0);
	lines.push_back(new Line(shaderFile, a, b));

}

Sonic::~Sonic()
{
	for (Marker* marker : markers)
		SAFE_DELETE(marker);
	SAFE_DELETE(backGround);
	for (Line* l : lines)
		SAFE_DELETE(l);
	
}

D3DXVECTOR2 mPos;
int stack_ = 0;
bool onMarker = false;
Marker* onMarked = nullptr;
void Sonic::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	backGround->Update(V, P);

	D3DXVECTOR2 mouse = Mouse->Position();
	D3DXVECTOR2 camera = values->MainCamera->Position();
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;

	mPos = mouse + camera;


	

	for (Line* l : lines)
	{
		l->Update(V, P);
	}

	CheckLines();
	
	player->Update(V, P);
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
