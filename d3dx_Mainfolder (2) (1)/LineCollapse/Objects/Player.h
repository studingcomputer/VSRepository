#pragma once
#include "Viewer/IFollowing.h"
#include "Renders/Line.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size);

	Sprite* GetSprite() { return animation->GetSprite(); }

	bool CheckCollapse_justforfloor(Line* line);
	bool CheckCollapse_justforsprite(Sprite* spr);

private:
	float moveSpeed;
	Animation* animation;

	D3DXVECTOR2 focusOffset;

	D3DXVECTOR2 velocity;
	bool onGround = true;
};