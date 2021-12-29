#pragma once
#include "Viewer/IFollowing.h"
#include "Renders/Line.h"

#define LRMove 0
#define BreakMove 1

#define LEFT true
#define RIGHT false


class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size);

	Sprite* GetSprite() { return animation->GetSprite(); }

	int CheckCollapse_justforfloor(Line* line);
	bool CheckCollapse_justforsprite(Sprite* spr);

	void Animation_Playing();

	bool RtOng() { return onGround; }

	PlayerAct RtStatus() { return status; }

private:
	float moveSpeed;
	Animation* animation;

	D3DXVECTOR2 focusOffset;

	D3DXVECTOR2 velocity;
	bool onGround = false;

	PlayerAct status;

	bool triggers[2] = {false, false};

	bool playerVec = LEFT;

	float val;
};