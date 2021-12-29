#include "stdafx.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusOffset(-180,-120), velocity(D3DXVECTOR2(0.0f,0.0f)), status(PlayerAct::Nothing)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"Momodora/86754.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	int a, b, c, d;

	Clip* clip;
	float clipSpeed1 = 0.1f;
	float clipSpeed2 = 0.13f;//idle
	//Idle, 0번째
	{
		clip = new Clip(PlayMode::Loop);
		a = 16;
		b = 2209;
		c = 18;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a+c, b+d), clipSpeed2);
		a = 65;
		b = 2209;
		c = 18;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed2);
		a = 113;
		b = 2209;
		c = 21;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed2);
		a = 161;
		b = 2209;
		c = 23;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed2);
		a = 210;
		b = 2209;
		c = 22;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed2);
		a = 260;
		b = 2209;
		c = 20;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed2);
		animation->AddClip(clip);
	}

	//Run, 1은 end, 2는 loop
	{
		clip = new Clip(PlayMode::End);
		a = 16;
		b = 854;
		c = 19;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 66;
		b = 854;
		c = 21;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		animation->AddClip(clip);
		clip = new Clip(PlayMode::Loop);
		a = 110;
		b = 854;
		c = 28;
		d = 35;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 161;
		b = 854;
		c = 26;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 213;
		b = 855;
		c = 19;
		d = 36;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 261;
		b = 856;
		c = 23;
		d = 35;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 306;
		b = 854;
		c = 27;
		d = 35;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 357;
		b = 854;
		c = 26;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 408;
		b = 854;
		c = 26;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 457;
		b = 856;
		c = 24;
		d = 35;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		animation->AddClip(clip);
	}

	//Break, 3번째
	{
		clip = new Clip(PlayMode::End);
		a = 12;
		b = 915;
		c = 20;
		d = 39;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 60;
		b = 916;
		c = 20;
		d = 38;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 110;
		b = 917;
		c = 20;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 160;
		b = 918;
		c = 22;
		d = 36;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 207;
		b = 918;
		c = 25;
		d = 36;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 258;
		b = 920;
		c = 20;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 309;
		b = 919;
		c = 19;
		d = 35;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		animation->AddClip(clip);
	}

	//Turn, 4번째
	{
		clip = new Clip(PlayMode::End);
		a = 19;
		b = 979;
		c = 20;
		d = 38;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 64;
		b = 981;
		c = 22;
		d = 36;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 112;
		b = 981;
		c = 22;
		d = 36;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	animation->DrawBound(false);
}

Player::~Player()
{
	SAFE_DELETE(animation);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->Position();

	
	if (!onGround)
	{
		velocity.y -= 9.8f * 0.00002f;
		animation->DrawCollision(false);
	}
	else
	{
		animation->DrawCollision(true);
	}
	bool _key = (Key->Press('A') && Key->Press('D'));
	if (Key->Press('A') && !_key)
	{
		if (status == PlayerAct::Turning || (playerVec != RIGHT))
		{
			playerVec = RIGHT;
			animation->RotationDegree(0, 0, 0);
			status = PlayerAct::Turning;
		}
		else
		{
			status = PlayerAct::MovingRight;
			velocity.x = -(moveSpeed * Timer->Elapsed());
			animation->RotationDegree(0, 180, 0);
		}
	}
	else if (Key->Press('D') && !_key)
	{
		if (status == PlayerAct::Turning || (playerVec != LEFT))
		{
			playerVec = LEFT;
			animation->RotationDegree(0, 180, 0);
			status = PlayerAct::Turning;
		}
		else
		{
			status = PlayerAct::MovingLeft;
			animation->RotationDegree(0, 0, 0);
			velocity.x = moveSpeed * Timer->Elapsed();
		}
	}
	else
	{
		if (velocity.x != 0.0f)
		{
			velocity.x = 0.0f;
			status = PlayerAct::Breaking;
			triggers[BreakMove] = true;
		}
		if (!triggers[BreakMove])
		{
			status = PlayerAct::Nothing;
			velocity.x = 0.0f;
		}
	}

	position.x += velocity.x;
	position.y += velocity.y;

	animation->Position(position);
	
	Animation_Playing();

	animation->Update(V, P);

}

void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);
	ImGui::LabelText("val", "%.2f", val);
	ImGui::LabelText("playerVec", "%s", playerVec ? "Left" : "Right");

	ImGui::LabelText("TurnCheck", "%s", (status == PlayerAct::Turning) ? "true" : "false");
	ImGui::LabelText("A_Check", "%s", (status == PlayerAct::Turning || (playerVec != RIGHT)) ? "true" : "false");
	ImGui::LabelText("D_Check", "%s", (status == PlayerAct::Turning || (playerVec != LEFT)) ? "true" : "false");


	ImGui::LabelText("first", "%s", (val < animation->Position().y - animation->TextureSize().y * 0.5f + 10.0f) ? "true" : "false");
	ImGui::LabelText("second", "%s", (val > animation->Position().y - animation->TextureSize().y * 0.5f - 2.0f) ? "true" : "false");
	animation->Render();

}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->Position() - focusOffset;
	(*size) = D3DXVECTOR2(1, 1);

}

int Player::CheckCollapse_justforfloor(Line * line)
{
	if (line->CheckCollapse(animation->GetSprite()))
	{
		val = line->GetYAxisWhereXIs(animation->Position().x);
		velocity.y = 0.0f;
		onGround = true;
		return 1;
	}
	else
	{
		val = line->GetYAxisWhereXIs(animation->Position().x);
		if ((val < animation->Position().y - animation->TextureSize().y * 0.5f + 10.0f) && (val > animation->Position().y - animation->TextureSize().y * 0.5f - 2.0f))
		{
			velocity.y = 0.0f;
			animation->Position(animation->Position().x, val + animation->TextureSize().y * 0.5f);
			onGround = true;
			return 2;
		}
		onGround = false;
	}
	return -1;
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

void Player::Animation_Playing()
{
	//animation->Play(bMove ? 1 : 0);
	if (status == PlayerAct::MovingRight || status == PlayerAct::MovingLeft)
	{
		if (animation->RtCurrentClip() == 1 && animation->Clip_Check_IfEnd())
		{
			animation->Play(2);
			triggers[LRMove] = true;
		}
		if (!triggers[LRMove])
		{
			animation->Play(1);
		}
	}
	else if (status == PlayerAct::Turning)
	{
		animation->Play(4);
		if (animation->Clip_Check_IfEnd())
		{
			triggers[BreakMove] = false;
			status = PlayerAct::Nothing;
		}
		triggers[LRMove] = true;
	}
	else if (status == PlayerAct::Breaking)
	{
		animation->Play(3);
		if (animation->Clip_Check_IfEnd())
		{
			triggers[BreakMove] = false;
		}
		triggers[LRMove] = false;
	}
	else
	{
		triggers[LRMove] = false;
		animation->Play(0);
	}
}
