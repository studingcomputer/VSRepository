#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, bool _where)
	:scale(1.0f, 1.0f), _where(_where)
{
	wstring SpriteFile = Textures + L"Momodora/86754.png";
	mainSprite = new Sprite(SpriteFile, shaderFile, 92, 3802, 114, 3805);

	position = start;
	mainSprite->Position(position);

	mainSprite->RotationDegree(0, _where ? 180 : 0, 0);
}

Bullet::~Bullet()
{
	SAFE_DELETE(mainSprite);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (hittedTrigger)
	{
		position = mainSprite->Position();
		if (_where)
		{
			position.x -= 300 * Timer->Elapsed();
		}
		else
		{
			position.x += 300 * Timer->Elapsed();
		}

	}

	mainSprite->Position(position);
	mainSprite->Update(V, P);
}

void Bullet::Render()
{
	mainSprite->Scale(scale);
	mainSprite->RotationDegree(rotation);
	mainSprite->Render();
}

bool Bullet::IsArrowHitAtWall(Sprite * obj)
{
	return false;
}
