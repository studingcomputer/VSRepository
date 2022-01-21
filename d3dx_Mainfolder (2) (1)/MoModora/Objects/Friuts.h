#pragma once
#include "Enemy.h"

class Friuts : public Enemy
{
public:
	Friuts(wstring shaderFile, D3DXVECTOR2 position);
	~Friuts();

	void Update(D3DXMATRIX V, D3DXMATRIX P) override;
	void Render() override;

	void HitBy_At(int damage) override;
	int RtStatus() { return (int)val->act; }


private:
	MainObject* val;
	float moveSpeed;
	void SetClip(wstring shaderFile, wstring textureFile, Clip * clip, int x, int y, int width, int height, float speed);

	bool attackAble = true;
	bool timerUpdate = false;
	bool metPlayer = false;

	void StatusSet();

	int currentAnimation;

	float TimePast;

	void StartTimer();
	int RtTimer();
	void ResetTimer();
};