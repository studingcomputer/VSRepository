#include "stdafx.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusOffset(-180,-120), velocity(D3DXVECTOR2(0.0f,0.0f)), status(PlayerAct::Nothing)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"Momodora/86754.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	float clipSpeed1 = 0.1f;
	float clipSpeed2 = 0.13f;//idle
	float clipSpeed3 = 0.03f;//landhard
	float clipSpeed4 = 0.08f;//landsoft

	//Idle, 0번째
	{
		clip = new Clip(PlayMode::Loop);
		SetClip(shaderFile, spriteFile, clip, 16, 2209, 18, 37, clipSpeed2);
		SetClip(shaderFile, spriteFile, clip, 65, 2209, 18, 37, clipSpeed2);
		SetClip(shaderFile, spriteFile, clip, 113, 2209, 21, 37, clipSpeed2);
		SetClip(shaderFile, spriteFile, clip, 161, 2209, 23, 37, clipSpeed2);
		SetClip(shaderFile, spriteFile, clip, 210, 2209, 22, 37, clipSpeed2);
		SetClip(shaderFile, spriteFile, clip, 260, 2209, 20, 37, clipSpeed2);
		animation->AddClip(clip);
	}

	//Run, 1은 end, 2는 loop
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 16, 854, 19, 37, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 66, 854, 21, 37, clipSpeed1);
		animation->AddClip(clip);
		clip = new Clip(PlayMode::Loop);
		SetClip(shaderFile, spriteFile, clip, 110, 854, 28, 35, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 161, 854, 26, 37, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 213, 855, 19, 36, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 261, 856, 23, 35, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 306, 854, 27, 35, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 357, 854, 26, 37, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 408, 854, 26, 37, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 457, 856, 24, 35, clipSpeed1);
		animation->AddClip(clip);
	}

	//Break, 3번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 12, 915, 20, 39, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 60, 916, 20, 38, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 110, 917, 20, 37, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 160, 918, 22, 36, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 207, 918, 25, 36, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 258, 920, 20, 34, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 309, 919, 19, 35, clipSpeed1);
		animation->AddClip(clip);
	}

	//Turn, 4번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 19, 979, 20, 38, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 64, 981, 22, 36, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 112, 981, 22, 36, clipSpeed1);
		animation->AddClip(clip);
	}

	//Crouch, 5번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 17, 1052, 18, 28, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 66, 1055, 18, 25, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 115, 1056, 19, 24, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 164, 1056, 19, 24, clipSpeed1);
		animation->AddClip(clip);
	}

	//Rise, 6번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 15, 1112, 20, 31, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 65, 1108, 19, 35, clipSpeed1);
		animation->AddClip(clip);
	}

	//Roll, 7번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 15, 3550, 23, 34, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 60, 3550, 32, 34, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 111, 3550, 24, 34, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 160, 3550, 25, 34, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 206, 3550, 30, 34, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 258, 3550, 23, 34, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 307, 3550, 20, 34, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 357, 3550, 21, 34, clipSpeed1);

		animation->AddClip(clip);
	}

	//Jump, 8번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 11, 1704, 24, 37, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 61, 1704, 23, 37, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 110, 1704, 23, 37, clipSpeed1);

		animation->AddClip(clip);
	}

	//Fall, 9번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 12, 1766, 24, 39, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 61, 1766, 25, 39, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 112, 1765, 24, 40, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 161, 1765, 24, 40, clipSpeed1);
		SetClip(shaderFile, spriteFile, clip, 210, 1765, 24, 40, clipSpeed1);

		animation->AddClip(clip);
	}

	//LandHard, 10번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 14, 3115, 21, 28, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 63, 3118, 21, 25, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 112, 3119, 22, 24, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 161, 3119, 22, 24, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 210, 3119, 22, 24, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 259, 3119, 22, 24, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 308, 3119, 22, 24, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 357, 3119, 22, 24, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 406, 3119, 22, 24, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 454, 3111, 22, 31, clipSpeed3);
		SetClip(shaderFile, spriteFile, clip, 506, 3108, 19, 35, clipSpeed3);

		animation->AddClip(clip);
	}

	//LandSoft, 11번째
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 14, 3177, 24, 29, clipSpeed4);
		SetClip(shaderFile, spriteFile, clip, 63, 3178, 24, 28, clipSpeed4);
		SetClip(shaderFile, spriteFile, clip, 111, 3175, 24, 28, clipSpeed4);
		SetClip(shaderFile, spriteFile, clip, 162, 3171, 19, 35, clipSpeed4);

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
				animation->Position(animation->Position().x, animation->Position().y - (S * 0.5f - animation->GetSprite()->TextureSize().y * 0.5f) );//이전 y 크기에 현재 y 크기를 빼면 변화량이 나옴, 이를 반으로 나누어 빼면 변화량 완성
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

void Player::SetClip(wstring shaderFile, wstring textureFile, Clip * clip, int x, int y, int width, int height, float speed)
{
	clip->AddFrame(new Sprite(textureFile, shaderFile, x, y, x + width, y + height), speed);
}