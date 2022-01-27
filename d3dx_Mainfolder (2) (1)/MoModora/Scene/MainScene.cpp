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
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save")) 
			{ 
				function<void(wstring)> f = bind(&MainScene::SaveComplete, this, placeholders::_1);

				Path::SaveFileDialog(L"", L"Binary\0*.bin", L".", f, Hwnd);
			}
			if (ImGui::MenuItem("Open")) 
			{
				function<void(wstring)> f = bind(&MainScene::OpenComplete, this, placeholders::_1);

				Path::OpenFileDialog(L"", L"Binary\0*.bin", L".", f, Hwnd);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
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
	if (ImGui::Button("Reset"))
	{
		isPlay = false;
		Reset_Process();
	}
	player->SetStart(isPlay);
	player->SetStart(isPlay);


	ImGui::End();

	backGround[mapSelect]->Render();
	player->Render();
	for (Line* l : lines)
	{
		l->Render();
	}
}

/*
	세이브 방법
	
	위치만 세이브한다.

	맵 종류 | 플레이어 위치 | ((-224, -224), 몬스터 위치) | ((-448, -448), 오브젝트 위치)
*/
void MainScene::SaveComplete(wstring name)
{
	BinaryWriter* w = new BinaryWriter;
	w->Open(name);

	vector<D3DXVECTOR2> v;
	v.push_back(D3DXVECTOR2(0, mapSelect));
	v.push_back(player->Position());
	for (Friuts* f : fruitDatabase)
		v.push_back(f->Position());

	w->UInt(v.size());
	w->Byte(&v[0], sizeof(D3DXVECTOR2) * v.size());

	w->Close();
	SAFE_DELETE(w);
}

void MainScene::OpenComplete(wstring name)
{

	for (Marker* marker : markers)
		SAFE_DELETE(marker);

	markers.clear();

	BinaryReader* r = new BinaryReader();
	r->Open(name);

	UINT count;
	count = r->UInt();

	vector<D3DXVECTOR2> v;
	v.assign(count, D3DXVECTOR2());

	void* ptr = (void*)&(v[0]);
	r->Byte(&ptr, sizeof(D3DXVECTOR2) * count);

	for (UINT i = 0; i < count; i++)
	{
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", v[i]));
	}

	r->Close();
	SAFE_DELETE(r);
}

void MainScene::Reset_Process()
{
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
