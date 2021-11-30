#pragma once

class Background
{
public:
	Background(wstring shaderFile);
	~Background();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(D3DXVECTOR2 _input);
	void Scale(D3DXVECTOR2 _input);

private:
	Sprite* main;
};