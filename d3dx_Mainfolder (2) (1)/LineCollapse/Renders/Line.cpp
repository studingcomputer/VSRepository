#include "stdafx.h"
#include "Line.h"

Line::Line(wstring shaderFile, D3DXVECTOR2& pos1, D3DXVECTOR2& pos2)
{
	//���� �����۾��� ���μ����� ���� �ʰ� ���ʿ� ��Ŀ�� ������ ����
	if (pos1.x <= pos2.x)
	{

		position1 = &pos1;
		position2 = &pos2;
	}
	else
	{

		position1 = &pos2;
		position2 = &pos1;
	}

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
	ResetEquation();
}

Line::~Line()
{
	SAFE_DELETE(shader);
}

void Line::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (position1->x > position2->x)
	{
		D3DXVECTOR2* temp = position1;
		position1 = position2;
		position2 = temp;
	}
	ResetEquation();
	vertices[0].Position = D3DXVECTOR3(position1->x, position1->y, 0.0f);//2��°���� �޸� ���� ���� �̻������� ���װ� ����(��ħ) �׷��� ��Ŀ�� ��ġ�� �ű� �� �޸� �ΰ��� ���������ϴ� �̻��� ���� �߻�(��ħ)
	vertices[1].Position = D3DXVECTOR3(position2->x, position2->y, 0.0f);

	DeviceContext->UpdateSubresource
	(
		vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 2, 0
	);
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	D3DXMATRIX S, T;

	D3DXMatrixScaling(&S, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&T, position1->x + Math::Round(position1->x - position2->x), GetYAxisWhereXIs(position1->x + Math::Round(position1->x - position2->x)), 0);

	world = S * T;

	shader->AsMatrix("World")->SetMatrix(world);
}

void Line::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset); 
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);



	shader->Draw(0, 0, 5);
}

bool Line::CheckCollapse(Sprite * input)
{
	if (!(
		(input->Position().x + input->TextureSize().x * 0.5f < position1->x) &&
		(input->Position().x - input->TextureSize().x * 0.5f > position2->x)
		))
	{
		float yAxis = GetYAxisWhereXIs(input->Position().x);
		if ((input->Position().y - input->TextureSize().y*0.5f > yAxis - 1) && (input->Position().y - input->TextureSize().y*0.5f < yAxis + 1))//�������� +-1
		{
			isContactHasOccured = true;
			return true;
		}
	}
	isContactHasOccured = false;
	return false;
}

float Line::GetYAxisWhereXIs(float _where)
{
	if (_where < position1->x || _where > position2->x) //�Լ��� �������� �� �̻��� �Ǿ������
		return -(2 * Height);//������ �����Ⱚ ����
	return inclination * _where + y_intercept;//y = ax + b
}

void Line::ResetEquation()
{
	float x = position1->x - position2->x;
	float y = position1->y - position2->y;
	inclination = y / x; // ���� = y ��ȭ�� / x ��ȭ��
	// a �˰� x, y�� �����ؼ� ���ϴ� y������ �� ������ ��Ÿ����: ax - y = -b
	y_intercept = -(inclination * position1->x - position1->y);
}
