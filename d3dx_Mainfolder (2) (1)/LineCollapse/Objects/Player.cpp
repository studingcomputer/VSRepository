#include "stdafx.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusOffset(-180,-120), velocity(D3DXVECTOR2(0.0f,0.0f))
{
	animation = new Animation;

	wstring spriteFile = Textures + L"Metalslug.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 2, 34, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 2, 64, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 64, 2, 94, 40), 0.3f);
		animation->AddClip(clip);
	}

	//Run
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 600, 64, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 65, 600, 96, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 97, 600, 124, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 125, 600, 154, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 158, 600, 188, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 191, 600, 222, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 224, 599, 258, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 259, 600, 294, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 295, 600, 326, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 329, 600, 360, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 362, 600, 393, 640), 0.1f);
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
	if (velocity.x != 0.0f)
		velocity.x = 0.0f;
	if (!onGround)
		velocity.y -= 9.8 * Timer->Elapsed();
	if (Key->Press('A'))
	{
		bMove = true;
		velocity.x = -( moveSpeed * Timer->Elapsed() );
		animation->RotationDegree(0, 180, 0);
	}
	else if (Key->Press('D'))
	{
		bMove = true;
		velocity.x = moveSpeed * Timer->Elapsed();
		animation->RotationDegree(0, 0, 0);
	}

	position.x += velocity.x;
	position.y += velocity.y;

	animation->Position(position);
	animation->Play(bMove ? 1 : 0);

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

bool Player::CheckCollapse_justforfloor(Line * line)
{
	if (line->CheckCollapse(animation->GetSprite()))
	{
		velocity.y = 0.0f;
		onGround = true;
		return true;
	}
	else
	{
		onGround = false;
	}
}

bool Player::CheckCollapse_justforsprite(Sprite * spr)
{
	if (Sprite::OBB(spr, animation->GetSprite()))
	{
		velocity.y = 0.0f;
		onGround = true;
		return true;
	}
	else
	{
		onGround = false;
	}
}
