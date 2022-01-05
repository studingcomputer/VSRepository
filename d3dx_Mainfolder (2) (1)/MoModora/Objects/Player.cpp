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
	float clipSpeed3 = 0.03f;//landhard
	float clipSpeed4 = 0.05f;//landsoft

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

	//Crouch, 5번째
	{
		clip = new Clip(PlayMode::End);
		a = 17;
		b = 1052;
		c = 18;
		d = 28;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 66;
		b = 1055;
		c = 18;
		d = 25;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 115;
		b = 1056;
		c = 19;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 164;
		b = 1056;
		c = 19;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		animation->AddClip(clip);
	}

	//Rise, 6번째
	{
		clip = new Clip(PlayMode::End);
		a = 15;
		b = 1112;
		c = 20;
		d = 31;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 65;
		b = 1108;
		c = 19;
		d = 35;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		animation->AddClip(clip);
	}

	//Roll, 7번째
	{
		clip = new Clip(PlayMode::End);
		a = 15;
		b = 3550;
		c = 23;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 60;
		b = 3550;
		c = 32;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 111;
		b = 3550;
		c = 24;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 160;
		b = 3550;
		c = 25;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 206;
		b = 3550;
		c = 30;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 258;
		b = 3550;
		c = 23;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 307;
		b = 3550;
		c = 20;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 357;
		b = 3550;
		c = 21;
		d = 34;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);

		animation->AddClip(clip);
	}

	//Jump, 8번째
	{
		clip = new Clip(PlayMode::End);
		a = 11;
		b = 1704;
		c = 24;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 61;
		b = 1704;
		c = 23;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 110;
		b = 1704;
		c = 23;
		d = 37;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);

		animation->AddClip(clip);
	}

	//Fall, 9번째
	{
		clip = new Clip(PlayMode::End);
		a = 12;
		b = 1766;
		c = 24;
		d = 39;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 61;
		b = 1766;
		c = 25;
		d = 39;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 112;
		b = 1765;
		c = 24;
		d = 40;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 161;
		b = 1765;
		c = 24;
		d = 40;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);
		a = 210;
		b = 1765;
		c = 24;
		d = 40;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed1);

		animation->AddClip(clip);
	}

	//LandHard, 10번째
	{
		clip = new Clip(PlayMode::End);
		a = 14;
		b = 3115;
		c = 21;
		d = 28;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 63;
		b = 3118;
		c = 21;
		d = 25;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 112;
		b = 3119;
		c = 22;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 161;
		b = 3119;
		c = 22;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 210;
		b = 3119;
		c = 22;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 259;
		b = 3119;
		c = 22;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 308;
		b = 3119;
		c = 22;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 357;
		b = 3119;
		c = 22;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 406;
		b = 3119;
		c = 22;
		d = 24;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 454;
		b = 3111;
		c = 22;
		d = 31;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);
		a = 506;
		b = 3108;
		c = 19;
		d = 35;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed3);

		animation->AddClip(clip);
	}

	//LandSoft, 11번째
	{
		clip = new Clip(PlayMode::End);
		a = 14;
		b = 3177;
		c = 24;
		d = 29;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed4);
		a = 63;
		b = 3178;
		c = 24;
		d = 28;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed4);
		a = 111;
		b = 3175;
		c = 24;
		d = 28;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed4);
		a = 162;
		b = 3171;
		c = 19;
		d = 35;
		clip->AddFrame(new Sprite(spriteFile, shaderFile, a, b, a + c, b + d), clipSpeed4);

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
		velocity.y -= 9.8f * 0.00002;//조정 심하게 필요(wndml) (완료)
		//velocity.y -= 9.8f * 0.000002;
		if (velocity.y < -0.05 && status != PlayerAct::Falling)
		{
			status = PlayerAct::Falling;
			WhereBegin_Fall = animation->Position().y;
		}
	}
	else
	{
		if (status == PlayerAct::Jumping)
			status = PlayerAct::Nothing;
		if (jumpStack != 0)
			jumpStack = 0;
	}

	Key_Check();
	

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
	ImGui::LabelText("Velocity", "%.2f, %.2f", velocity.x, velocity.y);

	ImGui::LabelText("BASIC_KEY", "%s", C_key ? "true" : "false");
	ImGui::LabelText("ELSE_KEY", "%s", Else_key ? "true" : "false");

	animation->Render();

}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->Position() - focusOffset;
	(*size) = D3DXVECTOR2(1, 1);

}

int Player::CheckCollapse_justforfloor(Line * line)
{
	if (status != PlayerAct::Jumping)
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
			if ((val < animation->Position().y - animation->TextureSize().y * 0.5f + 10.0f) && (val > animation->Position().y - animation->TextureSize().y * 0.5f - 10.0f))// +- 10 오차범위까지 처리
			{
				velocity.y = 0.0f;
				animation->Position(animation->Position().x, val + animation->TextureSize().y * 0.5f);
				onGround = true;
				return 2;
			}
			onGround = false;
		}
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
	switch (status)
	{
		case PlayerAct::Nothing:
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			animation->Play(0);
			break;

		case PlayerAct::MovingRight:
		case PlayerAct::MovingLeft:
			if (animation->RtCurrentClip() == 1 && animation->Clip_Check_IfEnd())
			{
				triggers[LRMove] = true;
			}
			if (!triggers[LRMove])
			{
				animation->Play(1);
			}
			else
			{
				animation->Play(2);
			}
			break;

		case PlayerAct::Turning:
			animation->Play(4);
			if (animation->Clip_Check_IfEnd())
			{
				triggers[BreakMove] = false;
				status = PlayerAct::Nothing;
			}
			triggers[LRMove] = true;
			break;

		case PlayerAct::Breaking:
			animation->Play(3);
			if (animation->Clip_Check_IfEnd())
			{
				triggers[BreakMove] = false;
			}
			triggers[LRMove] = false;
			break;

		case PlayerAct::Rising:
			animation->Play(6);
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
			}
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			break;

		case PlayerAct::Falling:
			animation->Play(9);
			if (velocity.y == 0)
			{
				if (WhereBegin_Fall - animation->Position().y <= 100)
					status = PlayerAct::LandSoft;
				else
					status = PlayerAct::LandHard;
				onGround = true;
			}
			break;

		case PlayerAct::Crouching:
			animation->Play(5);
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			break;

		case PlayerAct::Rolling:
			animation->Play(7);
			if (playerVec == LEFT)
				velocity.x = -(moveSpeed * 1.3f * Timer->Elapsed());
			else
				velocity.x = moveSpeed * 1.3f * Timer->Elapsed();
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
				isCharacterInvincibility = false;
				velocity.x = 0.0f;
			}
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			break;

		case PlayerAct::Jumping:
			animation->Play(8);
			break;

			//land 알고리즘
			/*
			1. 바닥에 닿으면, 일단 10애니메이션으로 초기화시켜주는 과정에서 10이 아니었다면 좌푯값을 재설정(바닥에 붙도록)
			2. 그 뒤는 앉았다 일어나는 건데, 그 과정에서 선에 빠지지 않도록 잘 조정해주어야 함.(제작중)
			3. 서는 모션까지 전부 완료시 idle 상태로 전환
			*/
		case PlayerAct::LandHard:
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			if (animation->RtCurrentClip() != 10)
			{
				S = animation->GetSprite()->TextureSize().y;
				animation->Play(10);
				animation->Position(animation->Position().x, animation->Position().y - (S - 2 * animation->GetSprite()->TextureSize().y) * 0.5f);
			}
			animation->Play(10);
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
			}
			break;

		case PlayerAct::LandSoft:
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			if (animation->RtCurrentClip() != 11)
			{
				S = animation->GetSprite()->TextureSize().y;//이전 y크기
				animation->Play(11);
				animation->Position(animation->Position().x, animation->Position().y - (S - 2 * animation->GetSprite()->TextureSize().y) * 0.5f);//이전 y 크기에 현재 y 크기를 빼면 변화량이 나옴, 이를 반으로 나누어 빼면 변화량 완성
			}
			animation->Play(11);
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
			}
			break;

	}
}

void Player::Key_Check()
{
	Run_key = (Key->Press('A') && Key->Press('D'));
	C_key = (status == PlayerAct::Falling || status == PlayerAct::Jumping || status == PlayerAct::Rolling);
	Else_key = (status == PlayerAct::Crouching || status == PlayerAct::Rising || status == PlayerAct::Turning || status == PlayerAct::LandHard || status == PlayerAct::LandSoft);
	if (Key->Down('C') && !C_key)//뭘 누르던지간에 c가 먼저 확인됨(현재로선)
	{
		if (status == PlayerAct::Crouching)
		{
			status = PlayerAct::Rising;
		}
		else
		{
			status = PlayerAct::Crouching;
			velocity.x = 0.0f;
		}
	}
	else if (Key->Down(VK_SHIFT) && !Else_key && !C_key)
	{
		status = PlayerAct::Rolling;
		//velocity.x = (velocity.x / Math::Round(velocity.x)) * (moveSpeed * 1.3 * Timer->Elapsed());//방향지정 필요함
		isCharacterInvincibility = true;
	}
	else if (Key->Down(VK_SPACE) && !Else_key)
	{
		onGround = false;
		if (jumpStack < 2)
		{
			if (jumpStack == 1)
			{
				status = PlayerAct::Jumping;
				velocity.y = moveSpeed * 0.0008;
			}
			else
			{
				status = PlayerAct::Jumping;
				velocity.y = moveSpeed * 0.001;
			}
			jumpStack++;
		}
	}
	else if (Key->Press('A') && !Run_key && !Else_key && !C_key)
	{
		if (status == PlayerAct::Turning || (playerVec != LEFT))
		{
			playerVec = LEFT;
			status = PlayerAct::Turning;
			velocity.x = 0.0f;
		}
		else
		{
			status = PlayerAct::MovingRight;
			velocity.x = -(moveSpeed * Timer->Elapsed());
		}
		animation->RotationDegree(0, 180, 0);
	}
	else if (Key->Press('D') && !Run_key && !Else_key && !C_key)
	{
		if (status == PlayerAct::Turning || (playerVec != RIGHT))
		{
			playerVec = RIGHT;
			status = PlayerAct::Turning;
			velocity.x = 0.0f;
		}
		else
		{
			status = PlayerAct::MovingLeft;
			velocity.x = moveSpeed * Timer->Elapsed();
		}
		animation->RotationDegree(0, 0, 0);
	}
	else if (!Else_key && !C_key)
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
}
