#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(300.0f), gravity(-9.8f)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"All.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(Textures + L"Mario/enemies.png", Shaders + L"009_Sprite.fx", 0, 4, 16, 20), 0.2f);
		clip->AddFrame(new Sprite(Textures + L"Mario/enemies.png", Shaders + L"009_Sprite.fx", 30, 4, 46, 20), 0.2f);
		animation->AddClip(clip);
	}

	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(Textures + L"Mario/enemies.png", Shaders + L"009_Sprite.fx", 60, 8, 76, 16), 0.2f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	ground_ = 0;
	bOnGround = false;
	velocity.x = -0.2;
}

Enemy::~Enemy()
{
}

void Enemy::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->Position();


	position.x += velocity.x;


	velocity.y += gravity * 0.0001f;
	if (!(bOnGround))
	{
		position.y += velocity.y;
	}

	if ((position.y <= ground_))
	{
		position.y = ground_;
		velocity.y = 0.0f;

		bOnGround = true;

	}



	animation->Position(position);

	animation->Update(V, P);

}

bool Enemy::Crash(int a, D3DXVECTOR2 pos_, D3DXVECTOR2 pos_axis)
{
	D3DXVECTOR2 get;

	switch (a)
	{
	case 1:
	{
		if (!notonfloor && velocity.y < 0.01)
		{
			ground_ = animation->Position().y;
			if (in_ground > ground_)
				in_ground = ground_;
			bOnGround = true;
			notonfloor = true;
			animation->Position(animation->Position().x, ground_);
		}
		return true;
	}
	case 2:
		velocity.y = -0.05f;

		return true;
	case 3:
		velocity.x = 0.2f;
		////velocity.y = -0.15f;
		//if (untilFloor)
		//	untilFloor = false;
		return true;
	case 4:
		Dead();
		//velocity.y = -0.15f;
		//if(untilFloor)
		//	untilFloor = false;
		return true;

	case -1:
		if ((notonfloor))
		{
			//(RtAn()->Position().y - RtAn()->TextureSize().y * 0.5f > ground_)
			if ((pos_.x + pos_axis.x * 0.5f < animation->Position().x - animation->TextureSize().x * 0.5f) || (pos_.x - pos_axis.x * 0.5f > animation->Position().x + animation->TextureSize().x * 0.5f))//벗어났는데 바닥보다 자신이 높게 있으면
			{
				ground_ = 0;//'블럭'과 충돌하지 않았으므로 기본값으로 전환
				bOnGround = false;
				notonfloor = false;
			}
		}
		break;
	}
	return false;
}

void Enemy::Dead()
{
	velocity = D3DXVECTOR2(0, 0);
	animation->Play(1);
}



void Enemy::Render()
{

	animation->Render();

}