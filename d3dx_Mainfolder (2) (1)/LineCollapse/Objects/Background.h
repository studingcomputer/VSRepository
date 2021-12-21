#pragma once

class Background
{
public:
	Background(wstring shaderFile);
	~Background();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Sprite* RtSpriteFor(int which);
private:
	Sprite* cloud[2];
	Sprite* bush[2];
	Sprite* tile[2];
};