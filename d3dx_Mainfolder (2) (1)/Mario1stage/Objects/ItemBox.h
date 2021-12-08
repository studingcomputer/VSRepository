#pragma once

class ItemBox
{
public:
	ItemBox(int _item, D3DXVECTOR2 _pos, D3DXVECTOR2 _scale);
	~ItemBox();

	void Update(D3DXMATRIX V, D3DXMATRIX P);
	void Render();

	Sprite* RtSpr();
	int RtItem() { return item; }
	int Under_Crash() { int temp = item; item = -1; return temp; }

private:
	Sprite* brick;
	Sprite* broken_brick;

	int item;
};