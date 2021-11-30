#include "stdafx.h"
#include "Camara.h"

Camara::Camara()
	: position(0, 0)
{
	D3DXMatrixIdentity(&view);
}

Camara::~Camara()
{
}

void Camara::Update()
{
	D3DXMatrixTranslation(&view, -position.x, -position.y, 0.0f);
}
