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
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(Vertex) * 2;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

Line::~Line()
{
	SAFE_DELETE(shader);
}

void Line::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	vertices[0].Position = D3DXVECTOR3(position1->x, position1->y, 0.0f);//2번째부터 메모리 안의 값이 이상해지는 버그가 있음(고침) 그런데 마커의 위치를 옮길 때 메모리 두개로 돌려막기하는 이상한 현상 발생(고침)
	vertices[1].Position = D3DXVECTOR3(position2->x, position2->y, 0.0f);

	DeviceContext->UpdateSubresource
	(
		vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 2, 0
	);
	D3DXMATRIX W;
	D3DXMATRIX S, T;

	D3DXMatrixIdentity(&W);

	D3DXMatrixScaling(&S, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&T, 0.0f, 0.0f, 0.0f);

	W = S * T;

	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
	shader->AsMatrix("World")->SetMatrix(W);
}

void Line::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);


	shader->Draw(0, (isContactHasOccured ? 1 : 0), 2);
}

bool Line::CheckCollapse(D3DXVECTOR2 pos, D3DXVECTOR2 scale)
{
	return false;
}
