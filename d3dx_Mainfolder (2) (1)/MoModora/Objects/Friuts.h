#pragma once
#include "Enemy.h"
class Enemy;

class Friuts : public Enemy
{
public:
	Friuts(wstring shaderFile, D3DXVECTOR2 position);
	~Friuts();

	virtual void Update(D3DXMATRIX V, D3DXMATRIX P) override;
	virtual void Render() override;

	virtual void HitBy_At(int damage) override;
	int RtStatus() { return (int)val->act; }

	D3DXVECTOR2 Position() { return val->_this->Position(); }

	void SetStart(bool val) { startTrigger = val; }
private:
	MainObject* val;
	float moveSpeed;
	void SetClip(wstring shaderFile, wstring textureFile, Clip * clip, int x, int y, int width, int height, float speed);

	bool attackAble = true;
	bool timerUpdate = false;
	bool metPlayer = false;
	bool startTrigger = false;

	void StatusSet();

	int currentAnimation;

	float TimePast;

	void StartTimer();
	int RtTimer();
	void ResetTimer();
};