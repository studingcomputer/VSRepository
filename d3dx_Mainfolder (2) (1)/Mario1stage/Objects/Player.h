#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void UpdatePos();
	void Render();

	void StartJump();


	Animation* RtAn() { return animation; }
	int RtGn() { return ground_; }

	bool Crash(int a, D3DXVECTOR2 pos_, D3DXVECTOR2 pos_axis);

	bool DoOnGround() { return bOnGround; }

	void Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size);
	
	//µð¹ö±ë¿ë

	D3DXVECTOR2 RtVelocity() { return velocity; }
	bool RtOnground() { return bOnGround; }
	int Rt_InGround() { return in_ground; }
	bool RtNotOnFloor() { return notonfloor; }

	bool IsDead();
private:
	float moveSpeed;
	D3DXVECTOR2 focusOffset;


	D3DXVECTOR2 velocity = D3DXVECTOR2(0.0f, 0.0f);
	float gravity;
	bool bOnGround;
	

	float ground_ = 0.0f;
	float in_ground = Height;

	bool notonfloor = false;


	Animation* animation;


private:

	void swap(int& a, int& b)
	{
		a = b;
	}
	void swap(float& a, float& b)
	{
		a = b;
	}

	D3DXVECTOR2 GetReflection(D3DXVECTOR2 vec) { return velocity + 2 * vec *(D3DXVec2Dot(&(-velocity), &vec)); }
};