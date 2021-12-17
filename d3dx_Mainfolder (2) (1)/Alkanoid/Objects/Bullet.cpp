#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
	:scale(1.0f, 1.0f), rotation(0,0,0), velocity(0.0f, 0.0f)
{
	clip = new Sprite(Textures + L"Arkanoid/Vaus.png", shaderFile, 40, 0, 45, 4);

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
	position = clip->Position();

	position.x += velocity.x * Timer->Elapsed();
	position.y += velocity.y * Timer->Elapsed();

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