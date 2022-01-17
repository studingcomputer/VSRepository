#pragma once
#include "Viewer/IFollowing.h"
#include "Renders/Line.h"

#define LRMove 0
#define BreakMove 1
#define StatusSensor 2

#define LEFT true
#define RIGHT false


class Player : public IFollowing
{
private:

	enum class _Attack
	{
		Nothing = 0,
		Leaf1,
		Leaf2,
		Leaf3,
		AirLeaf
	};

public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale, Sprite* worldSprite);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;

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

	bool triggers[3] = {false, false, false};

	bool playerVec = RIGHT;

	bool Run_key, C_key, Else_key, Attack_key;

	bool isCharacterInvincibility = false; // 무적판정

	int jumpStack = 0;
	int attackStack = 0;

	float WhereBegin_Fall = 0.0f;
	float FloorFall;

	float theEndofWorld_L;
	float theEndofWorld_R;

};