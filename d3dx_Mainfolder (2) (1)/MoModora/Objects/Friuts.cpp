#include "stdafx.h"
#include "Friuts.h"

Friuts::Friuts(wstring shaderFile, D3DXVECTOR2 position)
	:Enemy(val), moveSpeed(200.0f)
{
	TimePast = 0.0f;
	val = new MainObject(8, 2, EnemyStatus::nothing);

	this->position = position;
	wstring spriteFile = Textures + L"Momodora/93769.png";


	Clip* clip;
	float clipSpeed = 0.1f;

	//nothing
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 14, 65, 28, 23, clipSpeed);
		val->_this->AddClip(clip);
	}

	//walk
	{
		clip = new Clip(PlayMode::Loop);
		SetClip(shaderFile, spriteFile, clip, 14, 65, 28, 23, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 60, 64, 25, 24, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 106, 63, 23, 25, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 151, 65, 31, 23, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 196, 63, 33, 25, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 241, 62, 32, 26, clipSpeed);
		val->_this->AddClip(clip);
	}

	//hit 맞았을 때, 하나만 출력. 이후 유효타를 맞을때마다 번갈아가며 출력
	{
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 14, 113, 24, 28, 0.5f);
		val->_this->AddClip(clip);
		clip = new Clip(PlayMode::End);
		SetClip(shaderFile, spriteFile, clip, 59, 114, 24, 27, 0.5f);
		val->_this->AddClip(clip);
	}

	//attack
	{
		clip = new Clip(PlayMode::Loop);
		SetClip(shaderFile, spriteFile, clip, 32, 184, 24, 26, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 114, 179, 20, 31, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 180, 184, 46, 24, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 260, 186, 52, 21, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 341, 176, 58, 34, clipSpeed);//여기부터 유효타, 이 전까진 때리는 거로 캔슬 가능
		SetClip(shaderFile, spriteFile, clip, 423, 181, 58, 29, clipSpeed);
		SetClip(shaderFile, spriteFile, clip, 504, 181, 59, 29, clipSpeed);
		val->_this->AddClip(clip);
	}

	val->_this->Position(position);
	val->_this->Scale(D3DXVECTOR2(2.5f, 2.5f));
	val->_this->Play(0);
	vec = left;
}

Friuts::~Friuts()
{
	SAFE_DELETE(val->_this);
	SAFE_DELETE(val);
}

void Friuts::Update(D3DXMATRIX V, D3DXMATRIX P)
{
	if (startTrigger)
	{
		D3DXVECTOR2 ex_Position = val->_this->Position();

		if (timerUpdate)
			TimePast += Timer->Elapsed();

		StatusSet();

		if (val->act == EnemyStatus::nothing && !metPlayer)
		{
			StartTimer();
			if (RtTimer() >= 10)
			{
				ResetTimer();
				vec = Math::Random(0, 1) ? left : right;
				val->act = EnemyStatus::walking;
			}
		}


		attackAble = true;
		switch (val->act)
		{
			case EnemyStatus::walking:
				if (vec == left)
				{
					val->_this->RotationDegree(0, 180, 0);
					ex_Position.x -= moveSpeed * Timer->Elapsed();
				}
				else
				{
					val->_this->RotationDegree(0, 0, 0);
					ex_Position.x += moveSpeed * Timer->Elapsed();
				}
				break;

			case EnemyStatus::attacking:
				if (val->_this->GetClip()->RtCurrentFrame() < 4)
				{
					attackAble = true;
				}
				else
				{
					attackAble = false;
				}
		}
		val->_this->Position(ex_Position);
	}
	val->_this->Update(V, P);
}

void Friuts::Render()
{
	val->_this->Render();
}

void Friuts::HitBy_At(int damage)
{
	if (attackAble)
	{
		val->act = EnemyStatus::hit;
		val->HP -= damage;

		if (val->HP <= 0)
		{
			val->act = EnemyStatus::dead;
		}
		else if (currentAnimation == 1)
		{
			currentAnimation = 2;
		}
		else if (currentAnimation == 2)
		{
			currentAnimation = 1;
		}
	}
}

void Friuts::SetClip(wstring shaderFile, wstring textureFile, Clip * clip, int x, int y, int width, int height, float speed)
{
	clip->AddFrame(new Sprite(textureFile, shaderFile, x, y, x + width, y + height), speed);
}

void Friuts::StatusSet()
{
	switch (val->act)
	{
		case EnemyStatus::nothing:
			currentAnimation = 0;

		case EnemyStatus::walking:
			currentAnimation = 3;
			if (val->_this->Clip_Check_IfEnd())
			{
				val->act = EnemyStatus::nothing;
				currentAnimation = 0;
			}

		case EnemyStatus::hit:
			if(val->_this->Clip_Check_IfEnd())
			{
				val->act = EnemyStatus::nothing;
				currentAnimation = 0;
			}

		case EnemyStatus::attacking:
			currentAnimation = 4;
			if (val->_this->Clip_Check_IfEnd())
			{
				val->act = EnemyStatus::nothing;
				currentAnimation = 0;
			}
	}
	val->_this->Play(currentAnimation);
}

void Friuts::StartTimer()
{
	timerUpdate = true;
}

int Friuts::RtTimer()
{
	return TimePast;
}

void Friuts::ResetTimer()
{
	TimePast = 0.0f;
	timerUpdate = false;
}
