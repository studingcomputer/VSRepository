#include "stdafx.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(300.0f), gravity(-0.9f), focusOffset(-100, -185)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"All.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 74, 10, 74+41, 10 + 72), 1.0f);
		animation->AddClip(clip);
	}

	//Run
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 74, 10, 74 + 41, 10 + 72), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 10, 12, 10 + 41, 12 + 70), 0.1f);
		animation->AddClip(clip);
	}
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 138, 2, 138+41, 82), 0.5f);
		animation->AddClip(clip);
	}
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 7, 199 + 42,7+ 75), 0.5f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	ground_ = 0;
	bOnGround = false;
}

Player::~Player()
{
	SAFE_DELETE(animation);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	

	bool bMove = false;

	if (velocity.x < -0.00005)
		velocity.x += 0.00005f;
	else if (velocity.x > 0.00005)
		velocity.x -= 0.00005f;
	else
		velocity.x = 0.0f;

	if (Key->Press('A') && (animation->Position().x - animation->TextureSize().x * 0.5f > 0))
	{
		bMove = true;
		velocity.x = -(moveSpeed * Timer->Elapsed());
		animation->RotationDegree(0, 180, 0);
	}
	else if (Key->Press('D') && (animation->Position().x + animation->TextureSize().x * 0.5f < 8440))
	{
		bMove = true;
		velocity.x = moveSpeed * Timer->Elapsed();
		animation->RotationDegree(0, 0, 0);
	}

	
	

	if (!bOnGround && velocity.y > 0)
		animation->Play(2);
	else if (!bOnGround && velocity.y < 0)
		animation->Play(3);
	else
		animation->Play(bMove ? 1 : 0);

	animation->Update(V, P);



	


}
void Player::UpdatePos()
{
	D3DXVECTOR2 position = animation->Position();


	position.x += velocity.x;

	if (Key->Down(VK_SPACE))
	{
		StartJump();
	}

	velocity.y += gravity * 0.0001f;
	if (!(bOnGround))
	{
		position.y += velocity.y;

		animation->Position(position);
	}

	if (position.y <= ground_)
	{
		position.y = ground_;
		velocity.y = 0.0f;

		bOnGround = true;

		animation->Position(position);

	}


	animation->Position(position);
}
void Player::StartJump()
{
	if (bOnGround == true)
	{
		velocity.y = 0.2f;
		bOnGround = false;
	}
}

bool Player::Crash(int a, D3DXVECTOR2 pos_, D3DXVECTOR2 pos_axis)
{
	D3DXVECTOR2 get;

	switch (a)
	{
	case 1:
	{
		if (!notonfloor && velocity.y < 0.01)
		{
			swap(in_ground, ground_);
			ground_ = animation->Position().y;
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
		if (velocity.x < 0)
		{
			velocity.x = 0.0f;
		}
		////velocity.y = -0.15f;
		//if (untilFloor)
		//	untilFloor = false;
		return true;
	case 4:
		if (velocity.x > 0)
		{
			velocity.x = 0.0f;
		}
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
				swap(ground_, in_ground);//'블럭'과 충돌하지 않았으므로 기본값으로 전환
				bOnGround = false;
				notonfloor = false;
			}
		}
		break;
	}
	return false;
}

void Player::GotOn()
{
}


void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);

	animation->Render();

}


void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	if (animation->Position().x < Width * 0.5f + focusOffset.x)
	{
		(*position).x = Width * 0.5f;
		(*position).y = 115.0f - focusOffset.y;
		(*size) = D3DXVECTOR2(1, 1);
	}
	
	else if (animation->Position().x > 8440 - Width * 0.5f + focusOffset.x)
	{
		(*position).x = 8440 - Width * 0.5f;
		(*position).y = 115.0f - focusOffset.y;
		(*size) = D3DXVECTOR2(1, 1);
	}

	else
	{
		*position = animation->Position() - focusOffset;
		(*position).y = 115.0f - focusOffset.y;
		(*size) = D3DXVECTOR2(1, 1);
	}
}