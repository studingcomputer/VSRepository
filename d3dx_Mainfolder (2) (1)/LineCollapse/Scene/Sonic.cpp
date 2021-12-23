#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Objects/Marker.h"
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


	if (Mouse->Down(0) == true)
	{
		if (onMarker)
		{
			onMarker = false;
			onMarked = nullptr;
		}
		else
		{
			for (Marker* mark : markers)
			{
				if (Math::Round(mPos.x - mark->Position()->x) < 5, Math::Round(mPos.y - mark->Position()->y) < 5)
				{
					//마우스가 마커를 클릭했을때
					onMarker = true;
					onMarked = mark;
					break;
				}
			}
			if (onMarked == nullptr)
			{
				markers.push_back(new Marker(Shaders + L"009_Sprite.fx", mPos));
				stack_++;
				if (stack_ == 2)
				{
					stack_ = 0;
					// 첫번째 경우: 최근 생성된 마커의 수가 2개일 경우 그 2개의 마커 사이에 선을 생성
					lines.push_back(new Line(Shaders + L"009_Sprite.fx", *(markers[markers.size() - 2]->Position()), *(markers[markers.size() - 1]->Position())));
				}
			}
		}
		
	}

	if (onMarker)
	{
		onMarked->Position(mPos);
	}

	for (Marker* marker : markers)
	{
		marker->Update(V, P);
	}
	for (Line* l : lines)
	{
		l->Update(V, P);
	}
	for (Line* l : lines)
	{
		if (player->CheckCollapse_justforfloor(l))
			break;
	}
	player->Update(V, P);
}

void Sonic::Render()
{
	ImGui::LabelText("Position", "%.0f, %.0f", mPos.x, mPos.y);
	ImGui::LabelText("P_Position", "%.2f, %.2f", player->GetSprite()->Position().x, player->GetSprite()->Position().y);

	backGround->Render();
	for (Marker* marker : markers)
	{
		marker->Render();
	}
	player->Render();
	for (Line* l : lines)
	{
		l->Render();
	}

}
