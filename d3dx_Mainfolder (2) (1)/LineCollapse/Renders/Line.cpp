#include "stdafx.h"
#include "Line.h"

Line::Line(wstring shaderFile, D3DXVECTOR2& pos1, D3DXVECTOR2& pos2)
{
	//굳이 변경작업에 프로세스를 쓰지 않고 애초에 마커랑 포지션 공유
	position1 = &pos1;
	position2 = &pos2;

	shader = new Shader(shaderFile);
	vertices[0].Position = D3DXVECTOR3(position1->x, position1->y, 0.0f);
	vertices[1].Position = D3DXVECTOR3(position2->x, position2->y, 0.0f);

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 2;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

Line::~Line()
{
	SAFE_DELETE(shader);
}

void Line::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	vertices[0].Position = D3DXVECTOR3(position1->x, position1->y, 0.0f);//2번째부터 메모리 안의 값이 이상해지는 버그가 있음(고쳐야함)
	vertices[1].Position = D3DXVECTOR3(position2->x, position2->y, 0.0f);

	DeviceContext->UpdateSubresource
	(
		vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 2, 0
	);

	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	D3DXMATRIX S, T;

	D3DXMatrixScaling(&S, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&T, 0.0f, 0.0f, 0.0f);

	world = S * T;

	shader->AsMatrix("World")->SetMatrix(world);
}

void Line::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);


	shader->Draw(0, (isContactHasOccured ? 1 : 0), 5);
}

bool Line::CheckCollapse(D3DXVECTOR2 pos, D3DXVECTOR2 scale)
{
	return false;
}
