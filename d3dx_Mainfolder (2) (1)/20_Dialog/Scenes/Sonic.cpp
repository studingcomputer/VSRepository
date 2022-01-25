#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Objects/Marker.h"

Sonic::Sonic(SceneValues * values)
	:Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"Sonic.png", shaderFile);
	backGround->Position(0, 0);

	((Freedom*)(values->MainCamera))->Position(0, 0);
}

Sonic::~Sonic()
{
	for (Marker* marker : markers)
		SAFE_DELETE(marker);

	SAFE_DELETE(backGround);
}

D3DXVECTOR2 mPos;
void Sonic::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);

	D3DXVECTOR2 mouse = Mouse->Position();
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;
	D3DXVECTOR2 camera = values->MainCamera->Position();
	mPos = mouse + camera;

	if (Mouse->Down(0) == true)
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", mPos));

	for (Marker* marker : markers)
		marker->Update(V, P);
}

void Sonic::Render()
{


	if (ImGui::Button("Save Binary") == true)
	{
		function<void(wstring)> f = bind(&Sonic::SaveComplete, this, placeholders::_1);

		Path::SaveFileDialog(L"", L"Binary\0*.bin", L".", f, Hwnd);
	}
	
	if (ImGui::Button("Load Binary") == true)
	{
		function<void(wstring)> f = bind(&Sonic::OpenComplete, this, placeholders::_1);

		Path::OpenFileDialog(L"", L"Binary\0*.bin", L".", f, Hwnd);
	}

	
	ImGui::LabelText("Position", "%.0f, %.0f", mPos.x, mPos.y);
	
	backGround->Render();

	for (Marker* marker : markers)
		marker->Render();


}

void Sonic::SaveComplete(wstring name)
{
	BinaryWriter* w = new BinaryWriter;
	w->Open(name);

	vector<D3DXVECTOR2> v(markers.size());
	for (Marker* marker : markers)
		v.push_back(marker->Position());

	w->UInt(v.size());
	w->Byte(&v[0], sizeof(D3DXVECTOR2) * v.size());

	w->Close();
	SAFE_DELETE(w);
}

void Sonic::OpenComplete(wstring name)
{

	for (Marker* marker : markers)
		SAFE_DELETE(marker);
	
	markers.clear();

	BinaryReader* r = new BinaryReader();
	r->Open(name);

	UINT count;
	count = r->UInt();

	vector<D3DXVECTOR2> v;
	v.assign(count, D3DXVECTOR2());

	void* ptr = (void*)&(v[0]);
	r->Byte(&ptr, sizeof(D3DXVECTOR2) * count);

	for (UINT i = 0; i < count; i++)
	{
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", v[i]));
	}

	r->Close();
	SAFE_DELETE(r);
	
}
