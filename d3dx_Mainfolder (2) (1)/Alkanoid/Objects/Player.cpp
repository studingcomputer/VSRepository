#include "stdafx.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusOffset(-180,-120)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"Arkanoid/Vaus.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle_small
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 0, 32, 8), 0.3f);
		animation->AddClip(clip);
	}
	//Idle_large
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 8, 48, 16), 0.3f);
		animation->AddClip(clip);
	}

	//break
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 40, 32, 48), 1.0f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 40, 36, 82, 53), 1.0f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 91, 34, 135, 57), 1.0f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	animation->DrawBound(true);
}

Player::~Player()
{
	SAFE_DELETE(animation);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->Position();

	bool bMove = false;
	//±âµÕÀÇ ³ÐÀÌ: 30
	if (Key->Press('A') && animation->Position().x - animation->TextureSize().x * 0.5f > -306)
	{
		bMove = true;
		position.x -= moveSpeed * Timer->Elapsed();
		animation->RotationDegree(0, 180, 0);
	}
	else if (Key->Press('D') && animation->Position().x + animation->TextureSize().x * 0.5f < 306)
	{
		bMove = true;
		position.x += moveSpeed * Timer->Elapsed();
		animation->RotationDegree(0, 0, 0);
	}

	animation->Position(position);
	animation->Play(animationCnt);

	animation->Update(V, P);

}

void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);

	animation->Render();

}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->Position() - focusOffset;
	(*size) = D3DXVECTOR2(1, 1);

}
