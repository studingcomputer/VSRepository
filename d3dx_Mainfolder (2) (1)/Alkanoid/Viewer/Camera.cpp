#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	: position(-336,-406)
{
	D3DXMatrixIdentity(&view);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	D3DXMatrixTranslation(&view, -position.x, -position.y, 0.0f);
}
