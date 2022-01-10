#pragma once
#include "Viewer/IFollowing.h"
#include "Renders/Line.h"

#define LRMove 0
#define BreakMove 1

#define LEFT true
#define RIGHT false


class Player : public IFollowing
{
private:

	enum class _Attack
	{
		Leaf1 = 0,
		Leaf2,
		Leaf3,
		AirLeaf,
		Nothing
	};

public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size);

	Sprite* GetSprite() { return animation->GetSprite(); }
	Sprite* GetAttack_Crash() { return attack->GetSprite(); }

	int CheckCollapse_justforfloor(Line* line);
	bool CheckCollapse_justforsprite(Sprite* spr);

	void Animation_Playing();
	void Key_Check();

	bool RtOng() { return onGround; }

	PlayerAct RtStatus() { return status; }

	bool RtCharacterInvincibility() { return isCharacterInvincibility; }

private:
	float moveSpeed;
	Animation* animation;
	Animation* attack;

	void SetClip(wstring shaderFile, wstring textureFile, Clip* clip, int x, int y, int width, int height, float speed);

	D3DXVECTOR2 focusOffset;

	D3DXVECTOR2 velocity;
	bool onGround = false;

	PlayerAct status;
	_Attack attackStatus;

	bool triggers[2] = {false, false};

	bool playerVec = RIGHT;

	bool Run_key;
	bool C_key;
	bool Else_key;

	bool isCharacterInvincibility = false; // ��������

	int jumpStack = 0;
	int attackStack = 0;

	float WhereBegin_Fall = 0.0f;
	float FloorFall;

};