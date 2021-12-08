#include "stdafx.h"
#include "ItemBox.h"

ItemBox::ItemBox(int _item, D3DXVECTOR2 _pos, D3DXVECTOR2 _scale)
	:item(_item)
{

	brick = new Sprite(Textures + L"Mario/brick_query.png", Shaders + L"009_Sprite.fx", 0, 0, 16, 16);
	broken_brick = new Sprite(Textures + L"Mario/brick_query.png", Shaders + L"009_Sprite.fx", 16, 0, 32, 16);

	brick->Position(_pos);
	brick->Scale(_scale);
	broken_brick->Position(_pos);
	broken_brick->Scale(_scale);
}

ItemBox::~ItemBox()
{
	SAFE_DELETE(brick);
	SAFE_DELETE(broken_brick);
}

void ItemBox::Update(D3DXMATRIX V, D3DXMATRIX P)
{
	brick->Update(V, P);
	broken_brick->Update(V, P);

}

void ItemBox::Render()
{
	if (item != -1)
		brick->Render();
	else
		broken_brick->Render();
}

Sprite * ItemBox::RtSpr()
{
	if (item != -1)
		return brick;
	else
		return broken_brick;
}
