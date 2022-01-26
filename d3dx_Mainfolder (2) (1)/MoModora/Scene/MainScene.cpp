#include "stdafx.h"
#include "MainScene.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Renders/Line.h"
#include "Viewer/Following.h"
#include "Objects/Friuts.h"

MainScene::MainScene(SceneValues * values)
	:Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";


	backGround[0] = new Sprite(Textures + L"Momodora/sunsetmap.png", shaderFile);
	backGround[0]->Scale(1.05f, 1.05f);
	backGround[0]->Position(backGround[0]->TextureSize().x * 0.5f - Width * 0.5f, 0.0f);

	backGround[1] = new Sprite(Textures + L"Momodora/groundmap.png", shaderFile);
	backGround[1]->Scale(1.05f, 1.05f);
	backGround[1]->Position(backGround[0]->TextureSize().x * 0.5f - Width * 0.5f, 0.0f);

	backGround[2] = new Sprite(Textures + L"Momodora/icemap.png", shaderFile);
	backGround[2]->Scale(1.05f, 1.05f);
	backGround[2]->Position(backGround[0]->TextureSize().x * 0.5f - Width * 0.5f, 0.0f);

	lines.push_back(new Line(shaderFile, D3DXVECTOR2((backGround[mapSelect]->Position().x) - (backGround[mapSelect]->TextureSize().x * 0.5f), -(Height * 0.35f)), D3DXVECTOR2((backGround[mapSelect]->Position().x) + (backGround[mapSelect]->TextureSize().x * 0.5f), -(Height * 0.35f))));

	player = new Player(D3DXVECTOR2(-100, 100), D3DXVECTOR2(2.5f, 2.5f), backGround[mapSelect]);

	values->MainCamera = new Following(player);
}

MainScene::~MainScene()
{
	for(int i = 0; i < 3; i++)
		SAFE_DELETE(backGround[i]);
	for (Line* l : lines)
		SAFE_DELETE(l);
	SAFE_DELETE(player);
}

void MainScene::Update()
{

	values->MainCamera->Update();
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	backGround[mapSelect]->Update(values->MainCamera->View(), P);

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

void MainScene::Render()
{
	bool my_tool_active;

	ImGui::Begin("StageEditor", &my_tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Map"))
		{
			if (ImGui::MenuItem("SunSet_Map")) { mapSelect = 0; }
			if (ImGui::MenuItem("Ground_Map")) { mapSelect = 1; }
			if (ImGui::MenuItem("Winter_Map")) { mapSelect = 2; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	if (!isPlay)
	{
		if (ImGui::Button("Play"))
		{
			isPlay = true;
		}
	}
	else
	{
		if (ImGui::Button("Stop"))
		{
			isPlay = false;
		}
	}
	player->SetStart(isPlay);
	player->SetStart(isPlay);

	if (ImGui::Button("Save"))
	{
		// do stuff
	}

	ImGui::End();

	backGround[mapSelect]->Render();
	player->Render();
	for (Line* l : lines)
	{
		l->Render();
	}
}

void MainScene::CheckLines()
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
