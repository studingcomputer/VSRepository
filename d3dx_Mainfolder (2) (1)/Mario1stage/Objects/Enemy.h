#pragma once

class Enemy
{
public:
	Enemy(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Enemy();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	bool Crash(int a, D3DXVECTOR2 pos_, D3DXVECTOR2 pos_axis);

	void Dead();
	Animation* RtAn() { return animation; }
	Sprite* RtSp() { return animation->RtSp(); }
private:
	float moveSpeed;


	D3DXVECTOR2 velocity = D3DXVECTOR2(0.0f, 0.0f);
	float gravity;
	bool bOnGround;


	float ground_ = 0.0f;
	float in_ground = Height;

	bool notonfloor = false;

	Animation* animation;
};