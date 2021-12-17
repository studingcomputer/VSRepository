#pragma once

class Line
{
public:
	Line(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2);
	~Line();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	bool CheckCollapse(D3DXVECTOR2 pos, D3DXVECTOR2 scale);

	void Re_Build_Line(D3DXVECTOR2 pos);

private:

	D3DXVECTOR2 position1, position2;
};