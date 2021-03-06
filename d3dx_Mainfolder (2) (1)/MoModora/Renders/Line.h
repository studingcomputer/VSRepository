#pragma once

class Line
{
public:
	Line(wstring shaderFile, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2);
	~Line();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	bool CheckCollapse(Sprite* input);

	float GetYAxisWhereXIs(float _where);

private:


	void ResetEquation();

	D3DXVECTOR2 position1;
	D3DXVECTOR2 position2;

	struct Vertex
	{
		D3DXVECTOR3 Position;
	}; 
	Vertex vertices[2];

	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXMATRIX world;

	bool isContactHasOccured = false;

	float inclination;
	float y_intercept;
};