#pragma once

class Camara
{
public:
	Camara();
	virtual ~Camara();

	D3DXMATRIX View() { return view; }
	D3DXVECTOR2 Position() { return position; }

	virtual void Update();

protected:
	
	D3DXVECTOR2 position;

private:
	D3DXMATRIX view;
};