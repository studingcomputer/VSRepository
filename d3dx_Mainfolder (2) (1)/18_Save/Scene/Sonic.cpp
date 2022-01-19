#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Objects/Marker.h"

Sonic::Sonic(SceneValues * values)
	:Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backGround = new Sprite(Textures + L"Stage3.png", shaderFile);
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
	D3DXVECTOR2 camera = values->MainCamera->Position();
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;

	mPos = mouse + camera;

	if (Mouse->Down(0) == true)
	{
		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", mPos));
	}

	for (Marker* marker : markers)
	{
		marker->Update(V, P);
	}
}

void Sonic::Render()
{
	/*if (ImGui::Button("Save Text") == true)
	{
		FILE* fp = fopen("marker.txt", "w");

		fprintf(fp, "%d\n", markers.size());
		for (UINT i = 0; i < markers.size(); i++)
		{
			fprintf(fp, "%d, %f, %f\n", i, markers[i]->Position().x, markers[i]->Position().y);
		}
		fclose(fp);
	}

	if (ImGui::Button("Load text") == true)
	{
		if (Path::ExistFile("marker.txt") == true)
		{
			float start = Timer->Running();

			for (Marker* marker : markers)
			{
				SAFE_DELETE(marker);
			}
			markers.clear();
			FILE* fp = fopen("marker.txt", "r");
			
			UINT count;
			fscanf(fp, "%d", &count);

			for (UINT i = 0; i < count; i++)
			{
				UINT number;
				D3DXVECTOR2 position;

				fscanf(fp, "%d, %f, %f", &number, &position.x, &position.y);

				markers.push_back(new Marker(Shaders + L"009_Sprite.fx", position));
			}
			fclose(fp);
		}
	}*/

	//Binary

	if (ImGui::Button("Save Binary") == true)
	{
		BinaryWriter* w = new BinaryWriter;
		w->Open(L"marker.bin");

		vector<D3DXVECTOR2> v(markers.size());
		for (Marker* marker : markers)
			v.push_back(marker->Position());

		w->UInt(v.size());
		w->Byte(&v[0], sizeof(D3DXVECTOR2) * v.size());

		w->Close();
		SAFE_DELETE(w);
	}

	if (ImGui::Button("Load Binery") == true)
	{
		if (Path::ExistFile("marker.bin") == true)
		{
			float start = Timer->Running();

			for (Marker* marker : markers)
				SAFE_DELETE(marker);
			markers.clear();

			BinaryReader* r = new BinaryReader();
			r->Open(L"marker.bin");

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
	}




	ImGui::LabelText("Position", "%.0f, %.0f", mPos.x, mPos.y);

	for (Marker* marker : markers)
	{
		marker->Render();
	}

	backGround->Render();
}
