#pragma once
#include "stdafx.h"

#define left true
#define right false

enum class EnemyStatus
{
	nothing = 0,
	walking,
	attacking,
	hit,
	dead
};

struct MainObject
{
	Animation* _this;
	int HP;
	int attack;
	EnemyStatus act;

	MainObject(Animation* __this, int _HP, int _attack, EnemyStatus _act) : _this(__this), HP(_HP), attack(_attack), act(_act) {}
};

class Enemy
{
public:
	Enemy(MainObject* val)
	{
		status = val;
	}
	virtual ~Enemy() {}

	virtual void Update();
	virtual void Render();

	EnemyStatus WhatDoesEnemy() { return status->act; }
	virtual void HitBy_At();

protected:

	MainObject* status;
	D3DXVECTOR2 position;

	bool sawPlayer, onGround;
	bool vec;

};