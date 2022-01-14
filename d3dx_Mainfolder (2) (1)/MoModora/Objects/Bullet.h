#pragma once

class Sprite;

class Bullet
{
public:
	Bullet(wstring shaderFile, D3DXVECTOR2 start, bool _where);
	~Bullet();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	bool IsArrowHit(Sprite* obj) { return mainSprite->OBB(obj); }
	bool IsArrowHitAtWall(Sprite* obj);

	Sprite* RtSprite() { return mainSprite; }
private:
	Sprite* mainSprite;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	bool hittedTrigger = false;
	bool _where;
};