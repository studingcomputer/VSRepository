#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
	:scale(1.0f, 1.0f), rotation(0,0,0)
{
	clip = new Sprite(Textures + L"Bullets.png", shaderFile, x, 155, x + 11, 167);

	position = start;
	
	clip->Position(position);
	clip->DrawBound(true);
}

Bullet::~Bullet()
{
	SAFE_DELETE(clip);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	

	clip->Position(position);
	clip->Update(V, P);
}

void Bullet::Render()
{
	ImGui::Separator();

	ImGui::SliderFloat2("Bullet Scale", (float*)&scale, 1, 5);
	ImGui::SliderFloat3("Bullet Rotation", (float*)&rotation, 0, 360);	
	clip->Render();

	clip->Scale(scale);
	clip->RotationDegree(rotation);

	clip->Render();
}