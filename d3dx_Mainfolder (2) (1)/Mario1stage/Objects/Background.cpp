#include "stdafx.h"
#include "Background.h"

Background::Background(wstring shaderFile)
{
	wstring textureFile = L"";

	textureFile = L"../_Textures/Mario/Background_textured.png";
	
	main = new Sprite(textureFile, shaderFile);
}

Background::~Background()
{
	SAFE_DELETE(main);
}

void Background::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	main->Update(V, P);
}

void Background::Render()
{
	main->Render();
}

void Background::Position(D3DXVECTOR2 _input)
{
	main->Position(_input);
}

void Background::Scale(D3DXVECTOR2 _input)
{
	main->Scale(_input);
}
