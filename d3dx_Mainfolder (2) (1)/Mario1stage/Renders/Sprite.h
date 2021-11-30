#pragma once

class Sprite
{
public:
	Sprite(wstring textureFile, wstring shaderFile);
	Sprite(wstring texturefile, wstring shaderFile, float endX, float endY);
	Sprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY);
	virtual ~Sprite();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	D3DXVECTOR3 Rotation() { return rotation; }

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	D3DXVECTOR3 RotationDegree();

	D3DXVECTOR2 TextureSize() { return D3DXVECTOR2( textureSize.x * scale.x, textureSize.y * scale.y); }

	virtual int If_Met(D3DXVECTOR2 _pos, D3DXVECTOR2 _scale);

private:
	void Initialize(wstring spriteFile, wstring shaderFile, float startX, float startY, float endX, float endY);
	void UpdateWorld();


protected:
	wstring textureFile;

	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 textureSize;
	D3DXVECTOR3 rotation;

	ID3D11ShaderResourceView* srv;

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};
};

///////////////////////////////////////////////////////////////////////////////

class Sprites
{
private:
	friend class Sprite;

private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);

private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* SRV = NULL;
	};

	static map<wstring, SpriteDesc> spriteMap;
};
