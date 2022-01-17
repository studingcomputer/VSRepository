#include "stdafx.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale, Sprite* worldSprite)
	:moveSpeed(250.0f), focusOffset(Width * 0.5f, Height * 0.5f), velocity(D3DXVECTOR2(0.0f,0.0f)), status(PlayerAct::Nothing), attackStatus(_Attack::Nothing)
{
	animation = new Animation;
	attack = new Animation;

	wstring spriteFile = Textures + L"Momodora/86754.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	float clipSpeed1 = 0.1f;
	float clipSpeed2 = 0.13f;//idle
	float clipSpeed3 = 0.03f;//landhard
	float clipSpeed4 = 0.07f;

	{
		//player animation setting
		{
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
				SetClip(shaderFile, spriteFile, clip, 14, 3177, 24, 29, clipSpeed1);
				SetClip(shaderFile, spriteFile, clip, 63, 3178, 24, 28, clipSpeed1);
				SetClip(shaderFile, spriteFile, clip, 111, 3175, 24, 28, clipSpeed1);
				SetClip(shaderFile, spriteFile, clip, 162, 3171, 19, 35, clipSpeed1);

				animation->AddClip(clip);
			}

			//Attack1, 12번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 11, 87, 24, 36, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 58, 87, 26, 36, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 109, 91, 26, 32, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 163, 89, 27, 34, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 212, 89, 27, 34, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 261, 89, 27, 34, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 310, 89, 27, 34, clipSpeed4);

				animation->AddClip(clip);
			}

			//Attack2, 13번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 12, 149, 21, 37, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 61, 149, 22, 37, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 113, 151, 26, 35, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 158, 152, 29, 34, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 209, 152, 26, 34, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 258, 152, 25, 34, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 306, 152, 25, 34, clipSpeed4);

				animation->AddClip(clip);
			}

			//Attack3, 14번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 6, 215, 31, 34, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 51, 213, 34, 36, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 99, 213, 35, 36, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 148, 212, 32, 37, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 207, 212, 30, 37, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 207, 212, 30, 37, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 263, 221, 23, 28, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 303, 220, 29, 29, clipSpeed4);//----fromhere----
				SetClip(shaderFile, spriteFile, clip, 351, 220, 30, 29, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 400, 220, 30, 29, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 455, 220, 23, 29, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 506, 214, 19, 35, clipSpeed4);

				animation->AddClip(clip);
			}

			//jumpattack, 15번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 14, 274, 18, 36, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 62, 274, 18, 36, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 115, 281, 23, 29, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 164, 282, 23, 30, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 213, 283, 23, 29, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 262, 283, 23, 29, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 311, 282, 23, 30, clipSpeed4);
				animation->AddClip(clip);
			}

			//fallattack, 16번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 14, 339, 18, 36, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 62, 339, 18, 36, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 115, 346, 23, 29, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 165, 347, 22, 28, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 214, 348, 22, 27, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 263, 348, 22, 27, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 312, 348, 22, 27, clipSpeed4);
				animation->AddClip(clip);
			}
		}

		//attack animation setting
		{
			//Nothing, 0번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 1, 390, 1, 1, clipSpeed4);

				attack->AddClip(clip);
			}

			//leaf1, 1번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 1, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 98, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 195, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 305, 404, 58, 30, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 402, 404, 58, 30, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 499, 404, 58, 30, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 596, 404, 58, 30, clipSpeed4);

				attack->AddClip(clip);
			}

			//leaf2, 2번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 1, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 98, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 195, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 306, 463, 56, 38, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 403, 463, 56, 38, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 500, 463, 56, 38, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 597, 463, 56, 38, clipSpeed4);

				attack->AddClip(clip);
			}

			//leaf3, 3번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 1, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 98, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 195, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 98, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 195, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 195, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 195, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 399, 521, 65, 43, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 496, 521, 65, 43, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 593, 521, 65, 43, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 690, 521, 65, 43, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 787, 521, 65, 43, clipSpeed4);

				attack->AddClip(clip);
			}

			//airleaf, 4번째
			{
				clip = new Clip(PlayMode::End);
				SetClip(shaderFile, spriteFile, clip, 1, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 98, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 195, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 195, 390, 1, 1, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 225, 581, 38, 48, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 322, 581, 38, 48, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 419, 581, 38, 48, clipSpeed4);
				SetClip(shaderFile, spriteFile, clip, 516, 581, 38, 48, clipSpeed4);

				attack->AddClip(clip);
			}
		}
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	attack->Position(position);
	attack->Scale(scale);
	attack->Play(0);

	theEndofWorld_L = worldSprite->Position().x - worldSprite->TextureSize().x * 0.5f;
	theEndofWorld_R = worldSprite->Position().x + worldSprite->TextureSize().x * 0.5f;

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
		if (velocity.y < -0.05 && status != PlayerAct::Falling && !(status == PlayerAct::AirAttack_falling || status == PlayerAct::AirAttack_jumping))
		{
			status = PlayerAct::Falling;
			WhereBegin_Fall = animation->Position().y;
		}
	}
	else
	{
		if (attackStatus == _Attack::Nothing)//땅에 닿았으면서, 아무 공격도 하고 있지 않는다면
		{
			if (triggers[StatusSensor])
			{
				status = (PlayerAct)((int)PlayerAct::Attack1 + attackStack - 1);
				attackStatus = (_Attack)((int)_Attack::Leaf1 + attackStack - 1);
				triggers[StatusSensor] = false;
			}
			else
			{
				attackStack = 0;
			}
		}
		if (status == PlayerAct::Jumping)
			status = PlayerAct::Nothing;
		if (jumpStack != 0)
		{
			jumpStack = 0;
		}
	}

	Key_Check();
	

	position.x += velocity.x;
	position.y += velocity.y;

	animation->Position(position);
	float x_;
	if (!playerVec)
		x_ = position.x + attack->GetSprite()->TextureSize().x * 0.3f;
	else
		x_ = position.x - attack->GetSprite()->TextureSize().x * 0.3f;

	attack->Position(x_, position.y);
	
	Animation_Playing();

	animation->Update(V, P);
	attack->Update(V, P);

}

void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);
	ImGui::LabelText("val", "%.2f", FloorFall);
	ImGui::LabelText("playerVec", "%s", playerVec ? "Left" : "Right");
	ImGui::LabelText("Velocity", "%.2f, %.2f", velocity.x, velocity.y);

	ImGui::LabelText("BASIC_KEY", "%s", C_key ? "true" : "false");
	ImGui::LabelText("ELSE_KEY", "%s", Else_key ? "true" : "false");

	ImGui::LabelText("attackStack", "%d", attackStack);

	animation->Render();
	attack->Render();

}

int Player::CheckCollapse_justforfloor(Line * line)
{
	if (status != PlayerAct::Jumping)
	{
		if (line->CheckCollapse(animation->GetSprite()))
		{
			FloorFall = line->GetYAxisWhereXIs(animation->Position().x);
			velocity.y = 0.0f;
			onGround = true;
			return 1;
		}
		else
		{
			FloorFall = line->GetYAxisWhereXIs(animation->Position().x);
			if ((FloorFall < animation->Position().y - animation->TextureSize().y * 0.5f + 10.0f) && (FloorFall > animation->Position().y - animation->TextureSize().y * 0.5f - 10.0f))// +- 10 오차범위까지 처리
			{
				velocity.y = 0.0f;
				animation->Position(animation->Position().x, FloorFall + animation->TextureSize().y * 0.5f);
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
			if (onGround)
			{
				if (WhereBegin_Fall - animation->Position().y <= 100)
					status = PlayerAct::LandSoft;
				else
					status = PlayerAct::LandHard;
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
			1. 바닥에 닿으면, 일단 10애니메이션으로 초기화시켜주는 과정에서 10이 아니었다면 좌푯값을 재설정(바닥에 붙도록) * 이 부분 쓸모없는 부분으로 판단되어, 삭제됨
			2. 그 뒤는 앉았다 일어나는 건데, 그 과정에서 선에 빠지지 않도록 잘 조정해주어야 함.(제작완료)
			3. 서는 모션까지 전부 완료시 idle 상태로 전환
			*/
		case PlayerAct::LandHard:
			velocity.x = 0.0f;
			animation->Play(10);
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
			}
			break;

		case PlayerAct::LandSoft:
			velocity.x = 0.0f;
			animation->Play(11);
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
			}
			break;

		//다음은 공격 스택 및 공격 방법에 대해 설명하는 주석.
		/*
			처음은 그냥 공격.
			마우스 클릭으로 공격하는데 만약 띄엄띄엄 클릭한다면 Attack1만 반복.

			그러나 공격하는 도중 마우스가 다시 클릭되었을 경우,
			attackStack가 쌓이면서 다음 애니메이션으로 실행됨(물론 현재 실행 애니메이션 다음까지밖에 스택은 쌓이지 않는다. *Attack1 -> Attack3은 불가능하다는 뜻).

			또한 스택이 2 이상인 상태(처음 애니메이션과 다른 애니메이션이 나오고 있는 상태)에서 마우스 클릭을 그만한다면 스택은 0이 되고, 바로 IDLE로 들어간다.

			뛰는 경우는 위의 설명을 무시한다. 그냥 공격하며, 스택을 바닥에 닿았을 때 초기화한다. 또한 스택이 있는 경우 실행하지 않는다.(공중에 있는 경우 두번 공격하지 못한다.)
		*/

		case PlayerAct::Attack1:
			animation->Play(12);
			velocity.x = 0;
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
				attackStatus = _Attack::Nothing;
			}
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			break;

		case PlayerAct::Attack2:
			animation->Play(13);
			attackStatus = _Attack::Leaf2;
			velocity.x = 0;
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
				attackStatus = _Attack::Nothing;
			}
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			break;

		case PlayerAct::Attack3:
			animation->Play(14);
			attackStatus = _Attack::Leaf2;
			velocity.x = 0;
			if (animation->Clip_Check_IfEnd())
			{
				status = PlayerAct::Nothing;
				attackStatus = _Attack::Nothing;
			}
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			break;

		case PlayerAct::AirAttack_falling:
			animation->Play(15);
			attackStatus = _Attack::AirLeaf;
			velocity.x = 0;
			if (animation->Clip_Check_IfEnd() || onGround)
			{
				status = PlayerAct::Falling;
				attackStatus = _Attack::Nothing;
			}
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			break;

		case PlayerAct::AirAttack_jumping:
			animation->Play(16);
			attackStatus = _Attack::AirLeaf;
			velocity.x = 0;
			if (animation->Clip_Check_IfEnd() && velocity.y <= 0)
			{
				status = PlayerAct::Falling;
				attackStatus = _Attack::Nothing;
			}
			triggers[LRMove] = false;
			triggers[BreakMove] = false;
			break;
	}

	attack->Play((int)attackStatus);
}

void Player::Key_Check()
{
	Run_key = (Key->Press('A') && Key->Press('D'));
	C_key = (status == PlayerAct::Falling || status == PlayerAct::Jumping);
	Else_key = (status == PlayerAct::Crouching || status == PlayerAct::Rising || status == PlayerAct::Turning || status == PlayerAct::LandHard || status == PlayerAct::LandSoft || status == PlayerAct::Rolling);
	Attack_key = (status == PlayerAct::Attack1 || status == PlayerAct::Attack2 || status == PlayerAct::Attack3 || status == PlayerAct::AirAttack_falling || status == PlayerAct::AirAttack_jumping);
	if (Key->Down('C') && !C_key && !Attack_key)//뭘 누르던지간에 c가 먼저 확인됨(현재로선)
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
	else if (Key->Down(VK_SHIFT) && !Else_key && !C_key && !Attack_key)
	{
		status = PlayerAct::Rolling;
		//velocity.x = (velocity.x / Math::Round(velocity.x)) * (moveSpeed * 1.3 * Timer->Elapsed());//방향지정 필요함(필요하지 않기에 삭제됨)
		isCharacterInvincibility = true;
	}
	else if (Key->Down(VK_SPACE) && !Else_key && !Attack_key)
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
	else if (Key->Press('A') && !Run_key && !Else_key && !C_key && !Attack_key && (animation->Position().x - animation->TextureSize().x * 0.5f) > theEndofWorld_L)
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
		attack->RotationDegree(0, 180, 0);
	}
	else if (Key->Press('D') && !Run_key && !Else_key && !C_key && !Attack_key && (animation->TextureSize().x * 0.5f + animation->Position().x) < theEndofWorld_R)
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
		attack->RotationDegree(0, 0, 0);
	}
	else if (Mouse->Down(0) && !Else_key)
	{
		//다음은 공격 스택 및 공격 방법에 대해 설명하는 주석.
		/*
			처음은 그냥 공격.
			마우스 클릭으로 공격하는데 만약 띄엄띄엄 클릭한다면 Attack1만 반복.

			그러나 공격하는 도중 마우스가 다시 클릭되었을 경우,
			attackStack가 쌓이면서 다음 애니메이션으로 실행됨(물론 현재 실행 애니메이션 다음까지밖에 스택은 쌓이지 않는다. *Attack1 -> Attack3은 불가능하다는 뜻).

			또한 스택이 2 이상인 상태(처음 애니메이션과 다른 애니메이션이 나오고 있는 상태)에서 마우스 클릭을 그만한다면 스택은 0이 되고, 바로 IDLE로 들어간다.

			뛰는 경우는 위의 설명을 무시한다. 그냥 공격하며, 스택을 바닥에 닿았을 때 초기화한다. 또한 스택이 있는 경우 실행하지 않는다.(공중에 있는 경우 두번 공격하지 못한다.)
		*/
		if (!C_key)//뛰고 있거나 떨어지고 있는 게 아니라면(땅에 있음)
		{
			switch (attackStack)
			{
				case 0:
					attackStack++;//공격 스택: 1, 한번 마우스 클릭함.
					attackStatus = _Attack::Leaf1;
					status = PlayerAct::Attack1;
					break;

				case 1:
					attackStack++;//공격 스택: 2, 첫번째 공격 도중에 마우스 클릭함.
					triggers[StatusSensor] = true;
					break;

				case 2:
					if (attackStatus == _Attack::Leaf2)//첫번째 공격 도중에 복수 클릭이 감지되면 스택이 중복으로 쌓일 수 있으므로, 다음 애니메이션이 재생 중인 것을 확인한 뒤 증가.
					{
						triggers[StatusSensor] = true;
						attackStack++;//공격 스택: 3, 두번째 공격 도중에 마우스 클릭함.
					}
					break;
			}
			velocity.x = 0.0f;
		}
		else//위의 조건이 아니라면(뛰거나 떨어지고 있음)
		{
			if (attackStack == 0)
			{
				attackStack = 1;//일종의 트리거
				switch (status)
				{
					case PlayerAct::Falling:
						status = PlayerAct::AirAttack_falling;
						break;

					case PlayerAct::Jumping:
						status = PlayerAct::AirAttack_jumping;
						break;
				}
			}
		}
	}
	else if (!Else_key && !C_key && !Attack_key)
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

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	if (animation->Position().x < theEndofWorld_L + focusOffset.x)
	{
		(*position).x = focusOffset.x;
		(*position).y = focusOffset.y;
		(*size) = D3DXVECTOR2(1, 1);
	}

	else if (animation->Position().x > theEndofWorld_R - focusOffset.x)
	{
		(*position).x = theEndofWorld_R;
		(*position).y = focusOffset.y;
		(*size) = D3DXVECTOR2(1, 1);
	}

	else
	{
		*position = animation->Position() + focusOffset;
		(*position).y = focusOffset.y;
		(*size) = D3DXVECTOR2(1, 1);
	}
}