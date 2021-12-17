#pragma once

class Line
{
public:
	Line(wstring shaderFile, D3DXVECTOR2& pos1, D3DXVECTOR2& pos2);
	~Line();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	bool CheckCollapse(D3DXVECTOR2 pos, D3DXVECTOR2 scale);


private:

	D3DXVECTOR2* position1;
	D3DXVECTOR2* position2;

	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Color;
	}; 
	Vertex vertices[2];

	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXMATRIX world;

	bool isContactHasOccured = false;
};