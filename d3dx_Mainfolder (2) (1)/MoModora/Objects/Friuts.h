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


private:
	MainObject* val;
	float moveSpeed;
	void SetClip(wstring shaderFile, wstring textureFile, Clip * clip, int x, int y, int width, int height, float speed);

	bool attackAble = true;

	void StatusSet();

	int currentAnimation;
};