#pragma once
#include "Enemy.h"

class Friuts : public Enemy
{
public:
	Friuts(wstring shaderFile, D3DXVECTOR2 position);
	~Friuts();

	void Update() override;
	void Render() override;

	void HitBy_At() override;


private:
	MainObject* val;
	void SetClip(wstring shaderFile, wstring textureFile, Clip * clip, int x, int y, int width, int height, float speed);

};