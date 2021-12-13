#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size);

	Sprite* GetSprite() { return animation->GetSprite(); }

	void Animation_Change(int num) { animationCnt = num; }

private:
	float moveSpeed;
	Animation* animation;
	int animationCnt = 0;

	D3DXVECTOR2 focusOffset;
};