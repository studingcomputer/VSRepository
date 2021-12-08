#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background.h"
#include "Objects/Player.h"
#include "Objects/Enemy.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"
#include "Objects/ItemBox.h"


Background* bg;
Player* player;
vector<Sprite*> sprite;
vector<Sprite*> end_sprite;
vector<Sprite*> breakableBrick;


vector<ItemBox*> brick_Query;

Sprite* anEntrence;
Sprite* flag;
vector<Sprite*> floor_;
Camara* freeCam;
vector<Enemy *> Enemies;

vector<Sprite*> items;

bool CheckCollapse_floor();
bool CheckCollapse_Object();
bool MCheckCollapse_floor(int _where);
bool MCheckCollapse_Object(int _where);
bool CheckCollapse_End();


int res_debug;
int deadcount = 0;
bool isgameend = false;

void InitScene()
{

	bg = new Background(Shaders + L"/009_Sprite.fx");
	bg->Scale(D3DXVECTOR2(2.5f, 2.5f));
	bg->Position(D3DXVECTOR2(4220, 0));
	player = new Player(D3DXVECTOR2(5655, 300), D3DXVECTOR2(0.8f, 0.8f));


	freeCam = new Following(player);

	{//바닥 세팅작업
		floor_.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 0, 208, 1104, 208 + 32));
		floor_.back()->Position((1104 * 1.25f), 40);
		floor_.back()->Scale(2.5f, 2.5f);

		floor_.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1136, 208, 1136 + 240, 208 + 32));
		floor_.back()->Position((1136 * 2.5f) + (240 * 1.25f), 40);
		floor_.back()->Scale(2.5f, 2.5f);

		floor_.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1424, 208, 1424 + 1024, 208 + 32));
		floor_.back()->Position((1424 * 2.5f) + (1024 * 1.25f), 40);
		floor_.back()->Scale(2.5f, 2.5f);

		floor_.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2480, 208, 2480 + 896, 208 + 32));
		floor_.back()->Position((2480 * 2.5f) + (896 * 1.25f), 40);
		floor_.back()->Scale(2.5f, 2.5f);
	}

	{
		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 448, 176, 448 + 32, 176 + 32));
		sprite.back()->Position((448 + 16) * 2.5, (176 + 16)* 0.6f);
		sprite.back()->Scale(2.5f, 2.5f);

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1280, 80, 1391, 96));
		sprite.back()->Position(1335 * 2.5, 88 * 4.5);
		sprite.back()->Scale(2.5f, 2.5f);

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1456, 80, 1504, 96));
		sprite.back()->Position(1480 * 2.5, 88 * 4.5);
		sprite.back()->Scale(2.5f, 2.5f);

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 608, 160, 608 + 32, 160 + 48));
		sprite.back()->Position((608 + 16) * 2.5, (160 + 32)* 0.7f);
		sprite.back()->Scale(2.5f, 2.5f);

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 736, 144, 736 + 32, 144 + 64));
		sprite.back()->Position((736 + 16) * 2.5, (144 + 16)* 1.0f);
		sprite.back()->Scale(2.5f, 2.5f);

		//enterence
		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 912, 144, 912 + 32, 144 + 64));
		sprite.back()->Position((912 + 16) * 2.5, (144 + 16)* 1.0f);
		sprite.back()->Scale(2.5f, 2.5f);

		//exit
		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2608, 176, 2608 + 32, 176 + 32));
		sprite.back()->Position((2608 + 16) * 2.5, (176 + 16)* 0.6f);
		sprite.back()->Scale(2.5f, 2.5f);

		//2144 192 (4, total 4)

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2144, 192, 2144+64, 192+16));
		sprite.back()->Position(2176 * 2.5, 200 * 0.5);
		sprite.back()->Scale(2.5f, 2.5f);
		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2144 + 16, 192 - 16, 2144 + 64, 192));
		sprite.back()->Position((2176 + 8) * 2.5, 200 * 0.7);
		sprite.back()->Scale(2.5f, 2.5f);
		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2144 + 32, 192 - 32, 2144 + 64, 192 - 16));
		sprite.back()->Position((2176 + 16) * 2.5, 200 * 0.9);
		sprite.back()->Scale(2.5f, 2.5f);
		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2144 + 48, 192 - 48, 2144 + 64, 192 - 32));
		sprite.back()->Position((2176 + 24) * 2.5, 200 * 1.1);
		sprite.back()->Scale(2.5f, 2.5f);

		/////////////////////////////////////////////


		

		int a, b, c, d;

		a = 2240;
		b = 144;
		c = 16;
		d = 64;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.9);
		sprite.back()->Scale(2.5f, 2.5f);

		a = 2256;
		b = 160;
		c = 16;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c/2)) * 2.5, (b + (d/2)) * 1.05);
		sprite.back()->Scale(2.5f, 2.5f);

		a = 2256;
		b = 176;
		c = 32;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.75);
		sprite.back()->Scale(2.5f, 2.5f);

		a = 2256;
		b = 192;
		c = 48;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.5);
		sprite.back()->Scale(2.5f, 2.5f);

		a = 2368;
		b = 192;
		c = 64;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.5);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2384;
		b = 176;
		c = 48;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.75);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2400;
		b = 160;
		c = 32;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 1.061);
		sprite.back()->Scale(2.5f, 2.5f);

		a = 2416;
		b = 144;
		c = 16;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 1.4358);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2432;
		b = 144;
		c = 16;
		d = 64;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.898);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2480;
		b = 144;
		c = 16;
		d = 64;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.9);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2496;
		b = 160;
		c = 16;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 1.05);
		sprite.back()->Scale(2.5f, 2.5f);

		a = 2496;
		b = 176;
		c = 32;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.75);
		sprite.back()->Scale(2.5f, 2.5f);

		a = 2496;
		b = 192;
		c = 48;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.49);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2896;
		b = 192;
		c = 128;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.5);
		sprite.back()->Scale(2.5f, 2.5f);

		a = 2912;
		b = 176;
		c = 112;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.76);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2928;
		b = 160;
		c = 96;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 1.07);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2944;
		b = 144;
		c = 80;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 1.44);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2960;
		b = 128;
		c = 64;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 1.9);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2976;
		b = 112;
		c = 48;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 2.488);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 2992;
		b = 96;
		c = 32;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 3.257);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 3008;
		b = 80;
		c = 16;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 4.299);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 3024;
		b = 80;
		c = 16;
		d = 128;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 1.66);
		sprite.back()->Scale(2.5f, 2.5f);


		a = 3160;
		b = 49;
		c = 16;
		d = 16;

		flag=new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d);
		flag->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 8);
		flag->Scale(2.5f, 2.5f);

		a = 3175;
		b = 48;
		c = 2;
		d = 144;

		end_sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		end_sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 2.502);
		end_sprite.back()->Scale(2.5f, 2.5f);

		a = 3172;
		b = 40;
		c = 8;
		d = 8;

		end_sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		end_sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 11.1);
		end_sprite.back()->Scale(2.5f, 2.5f);

		a = 3168;
		b = 192;
		c = 16;
		d = 16;

		sprite.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", a, b, a + c, b + d));
		sprite.back()->Position((a + (c / 2)) * 2.5, (b + (d / 2)) * 0.5);
		sprite.back()->Scale(2.5f, 2.5f);
	}

	{
		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 320, 144, 337, 160));
		breakableBrick.back()->Position(328 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 351, 144, 369, 160));
		breakableBrick.back()->Position(360 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 383, 144, 400, 160));
		breakableBrick.back()->Position(391 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1232, 144, 1249, 160));
		breakableBrick.back()->Position(1240 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);
		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1263, 144, 1280, 160));
		breakableBrick.back()->Position(1271 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);


		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1504, 144, 1504+16, 160));
		breakableBrick.back()->Position(1512 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		
		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1600, 144, 1616, 160));
		breakableBrick.back()->Position(1608 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1616, 144, 1632, 160));
		breakableBrick.back()->Position(1624 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1888, 144, 1888+16, 160));
		breakableBrick.back()->Position(1896 * 2.5, 152 * 1.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		//1936 : 48

		for (int i = 0; i <= 3; i++)
		{
			breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 1936 + 16*i, 80, 1936 + 16 * (i + 1), 95));
			breakableBrick.back()->Position((1936 + (16 * i) + 8) * 2.5, 87 * 4.5);
			breakableBrick.back()->Scale(2.5f, 2.5f);
		}
		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2048, 80, 2064, 95));
		breakableBrick.back()->Position(2054 * 2.5, 87 * 4.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2095, 80, 2111, 95));
		breakableBrick.back()->Position(2103 * 2.5, 87 * 4.5);
		breakableBrick.back()->Scale(2.5f, 2.5f);

		//2064
		for (int i = 0; i < 2; i++)
		{
			breakableBrick.push_back(new Sprite(Textures + L"Mario/background.png", Shaders + L"009_Sprite.fx", 2064 + 16 * i, 144, 2064 + 16 * (i + 1), 160));
			breakableBrick.back()->Position((2064 + (16 * i) + 8) * 2.5, 152 * 1.5);
			breakableBrick.back()->Scale(2.5f, 2.5f);
		}
	}

	{
		Enemies.push_back(new Enemy(D3DXVECTOR2(1400, 140), D3DXVECTOR2(2.5f, 2.5f))); 
		Enemies.push_back(new Enemy(D3DXVECTOR2(5700, 140), D3DXVECTOR2(2.5f, 2.5f)));
		Enemies.push_back(new Enemy(D3DXVECTOR2(7000, 140), D3DXVECTOR2(2.5f, 2.5f)));
	}

	{
		brick_Query.push_back(new ItemBox(1, D3DXVECTOR2((328 * 2.5 + 360 * 2.5) * 0.5, 152 * 1.5), D3DXVECTOR2(2.5f, 2.5f)));
		brick_Query.push_back(new ItemBox(0, D3DXVECTOR2((328 * 2.5 + 360 * 2.5) * 0.5, 152 * 1.5), D3DXVECTOR2(2.5f, 2.5f)));
	}

	{
		items.push_back(new Sprite(Textures + L"Mario/flower.png", Shaders + L"009_Sprite.fx"));
		breakableBrick.back()->Position(-1000, -1000);
		breakableBrick.back()->Scale(2.5f, 2.5f);
	}

}

void DestroyScene()
{
	for (Sprite* spr : sprite)
	{
		SAFE_DELETE(spr);
	}
	sprite.clear();

	SAFE_DELETE(player);

	SAFE_DELETE(bg);

	SAFE_DELETE(freeCam);

	for (Sprite* spr : floor_)
	{
		SAFE_DELETE(spr);
	}
	floor_.clear();
	for (Sprite* spr : breakableBrick)
	{
		SAFE_DELETE(spr);
	}
	breakableBrick.clear();
	for (Sprite* spr : end_sprite)
	{
		SAFE_DELETE(spr);
	}
	end_sprite.clear();
	SAFE_DELETE(flag);
	for (Enemy* an : Enemies)
	{
		SAFE_DELETE(an);
	}
	Enemies.clear();
	for (ItemBox* box : brick_Query)
		SAFE_DELETE(box);
}

D3DXMATRIX V, P;
void Update()
{
	if (!isgameend)
	{
		//View
		freeCam->Update();

		//Projection
		D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

		bg->Update(freeCam->View(), P);

		bool res = false;

		





		for (Sprite* spr : sprite)
			spr->Update(freeCam->View(), P);
		if (breakableBrick.size() > 0)
			for (Sprite* spr : breakableBrick)
				spr->Update(freeCam->View(), P);
		for (ItemBox* box : brick_Query)
			box->Update(freeCam->View(), P);
		for (Sprite* spr : floor_)
			spr->Update(freeCam->View(), P);
		for (Sprite* spr : end_sprite)
			spr->Update(freeCam->View(), P);
		flag->Update(freeCam->View(), P);
		for (Enemy* an : Enemies)
		{
			an->Update(freeCam->View(), P);
		}

		if (!CheckCollapse_floor())
		{
			CheckCollapse_Object();
			if (CheckCollapse_End())
			{
				isgameend = true;
			}
		}
		for (int i = 0; i < Enemies.size(); i++)
		{
			if (!MCheckCollapse_floor(i))
			{
				MCheckCollapse_Object(i);
			}
			//enemy 작성
		}

		player->UpdatePos();

		player->Update(freeCam->View(), P);

		if (player->IsDead())
		{
			//죽었을 때 처리
			MessageBox(NULL, L"플레이어가 죽었습니다", L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
			if (deadcount++ > 0)
			{
				wstring s = to_wstring(deadcount) + L"번째 죽음";
				LPCWSTR message = (LPCWSTR)s.c_str();
				MessageBox(NULL, message, L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
			}

			DestroyScene();
			InitScene();
		}
	}
	else
	{
		//View
		freeCam->Update();

		//Projection
		D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

		bg->Update(freeCam->View(), P);

		bool res = false;

		for (Sprite* spr : items)
		{
			spr->Update(freeCam->View(), P);
		}




		
		for (Sprite* spr : sprite)
			spr->Update(freeCam->View(), P);
		if (breakableBrick.size() > 0)
			for (Sprite* spr : breakableBrick)
				spr->Update(freeCam->View(), P);
		for (ItemBox* box : brick_Query)
			box->Update(freeCam->View(), P);
		
		for (Sprite* spr : floor_)
			spr->Update(freeCam->View(), P);
		for (Sprite* spr : end_sprite)
			spr->Update(freeCam->View(), P);
		for (Enemy* an : Enemies)
			an->Update(freeCam->View(), P);
		if (flag->Position().y > 150)
			flag->Position(D3DXVECTOR2(flag->Position().x, flag->Position().y + (-0.5)));

		flag->Update(freeCam->View(), P);

		player->WalkTo(8170, freeCam->View(), P);


	}
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		bg->Render();

		player->Render();
		for (Sprite* spr : sprite)
			spr->Render();
		if (breakableBrick.size() > 0)
			for (Sprite* spr : breakableBrick)
				spr->Render();

		for (ItemBox* spr : brick_Query)
			spr->Render();

		for (Sprite* spr : items)
			spr->Render();

		flag->Render();
		for (Sprite* spr : floor_)
			spr->Render();
		for (Sprite* spr : end_sprite)
			spr->Render();
		for (Enemy* an : Enemies)
			an->Render();
		//-----------debug--------------
		string scoreString = "x = " + to_string(player->RtAn()->Position().x);
		scoreString += " y = " + to_string(player->RtAn()->Position().y);

		ImGui::Text(scoreString.c_str());

		scoreString = "x = " + to_string(player->RtVelocity().x);
		scoreString += " y = " + to_string(player->RtVelocity().y);

		ImGui::Text(scoreString.c_str());

		scoreString = "onground = " + to_string(player->RtOnground());

		scoreString += " notonfloor = " + to_string(player->RtNotOnFloor());

		scoreString += " checkdebug = " + to_string(res_debug);

		ImGui::Text(scoreString.c_str());

		scoreString = "ground = " + to_string(player->RtGn());
		ImGui::Text(scoreString.c_str());

		scoreString = "in_ground = " + to_string(player->Rt_InGround());
		ImGui::Text(scoreString.c_str());
		//-----------debug--------------
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}





bool CheckCollapse_floor()
{
	int dbdebug[2] = { -7, -7 };
	Sprite* sprdb[2] = { nullptr, nullptr };

	for (Sprite* spr : sprite)
	{
		if (!(
			(spr->Position().x - spr->TextureSize().x * 0.5f > freeCam->Position().x + Width) ||
			(spr->Position().x + spr->TextureSize().x * 0.5f < freeCam->Position().x)
			))
		{
			res_debug = spr->If_Met(player->RtAn()->Position(), player->RtAn()->TextureSize());
			if (player->Crash(res_debug, spr->Position(), spr->TextureSize()))
			{
				if ((sprdb[0] == nullptr) || (res_debug == 1))
				{
					dbdebug[0] = res_debug;
					sprdb[0] = spr;
				}
			}
		}
	}
	for (Sprite* spr : floor_)
	{
		if (!(
			(spr->Position().x - spr->TextureSize().x * 0.5f > freeCam->Position().x + Width) ||
			(spr->Position().x + spr->TextureSize().x * 0.5f < freeCam->Position().x)
			))
		{
			res_debug = spr->If_Met(player->RtAn()->Position(), player->RtAn()->TextureSize());
			if (player->Crash(res_debug, spr->Position(), spr->TextureSize()))
			{
				dbdebug[1] = res_debug;
				sprdb[1] = spr;
				break;
			}
		}
	}

	if ((dbdebug[0] != -7 && dbdebug[1] != -7) || (dbdebug[1] != -7 && dbdebug[0] == -7))
	{
		player->Crash(dbdebug[1], sprdb[1]->Position(), sprdb[1]->TextureSize());
		return true;
	}
	else if (dbdebug[1] == -7 && dbdebug[0] != -7)
	{
		player->Crash(dbdebug[0], sprdb[0]->Position(), sprdb[0]->TextureSize());
		return true;
	}
	for (Enemy* enemy : Enemies)
	{
		if (!(
			(enemy->RtSp()->Position().x - enemy->RtSp()->TextureSize().x * 0.5f > freeCam->Position().x + Width) ||
			(enemy->RtSp()->Position().x + enemy->RtSp()->TextureSize().x * 0.5f < freeCam->Position().x)
			))
		{
			int result = enemy->RtSp()->If_Met(player->RtAn()->Position(), player->RtAn()->TextureSize());

			result = player->Crash(result, enemy->RtSp()->Position(), enemy->RtSp()->TextureSize());

			if (result)
			{
				if (result == 1)
				{
					enemy->Dead();
				}
				else
				{
					if (player->LvDown())
					{
						isgameend = true;
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool CheckCollapse_Object()
{
	//아래의 코드는 충돌확인
	//뭐 하나라도 닿으면 바로 true 리턴으로 인한 함수종료가 일어남
	//이하 생략
	for (Sprite* spr : breakableBrick)
	{
		if (!(
			(spr->Position().x - spr->TextureSize().x * 0.5f > freeCam->Position().x + Width) ||
			(spr->Position().x + spr->TextureSize().x * 0.5f < freeCam->Position().x)
			))
		{
			int result = spr->If_Met(player->RtAn()->Position(), player->RtAn()->TextureSize());

			

			if (player->Crash(result, spr->Position(), spr->TextureSize()))
			{
				if (result == 2)
				{
					breakableBrick.erase(std::find(breakableBrick.begin(), breakableBrick.end(), spr));//삭제
				}
				return true;
			}
		}
	}
	
	for (ItemBox* spr : brick_Query)
	{
		if (!(
			(spr->RtSpr()->Position().x - spr->RtSpr()->TextureSize().x * 0.5f > freeCam->Position().x + Width) ||
			(spr->RtSpr()->Position().x + spr->RtSpr()->TextureSize().x * 0.5f < freeCam->Position().x)
			))
		{
			int res = spr->RtSpr()->If_Met(player->RtAn()->Position(), player->RtAn()->TextureSize());
			if (res == 2 && spr->RtItem() != -1)
			{
				spr->Under_Crash();
				items.back()->Position(spr->RtSpr()->Position().x, (spr->RtSpr()->Position().y + spr->RtSpr()->TextureSize().y * 0.5f) + items.back()->TextureSize().y *0.5f);
				return true;
			}
			else if (player->Crash(res, spr->RtSpr()->Position(), spr->RtSpr()->TextureSize()))
			{
				return true;
			}
		}
	}
	return false;
}


bool CheckCollapse_End()
{
	for (Sprite* spr : end_sprite)
	{
		if (!(
			(spr->Position().x - spr->TextureSize().x * 0.5f > freeCam->Position().x + Width) ||
			(spr->Position().x + spr->TextureSize().x * 0.5f < freeCam->Position().x)
			))
		{
			res_debug = spr->If_Met(player->RtAn()->Position(), player->RtAn()->TextureSize());
			if (player->Crash(res_debug, spr->Position(), spr->TextureSize()))
			{
				return true;
			}
		}
	}
	return false;
}


bool MCheckCollapse_floor(int _where)
{
	int dbdebug[2] = { -7, -7 };
	Sprite* sprdb[2] = { nullptr, nullptr };

	for (Sprite* spr : sprite)
	{
		res_debug = spr->If_Met(Enemies[_where]->RtAn()->Position(), Enemies[_where]->RtAn()->TextureSize());
		if (Enemies[_where]->Crash(res_debug, spr->Position(), spr->TextureSize()))
		{
			if ((sprdb[0] == nullptr) || (res_debug == 1))
			{
				dbdebug[0] = res_debug;
				sprdb[0] = spr;
			}
		}
	}
	for (Sprite* spr : floor_)
	{
			res_debug = spr->If_Met(Enemies[_where]->RtAn()->Position(), Enemies[_where]->RtAn()->TextureSize());
			if (Enemies[_where]->Crash(res_debug, spr->Position(), spr->TextureSize()))
			{
				dbdebug[1] = res_debug;
				sprdb[1] = spr;
				break;
			}
	}

	if ((dbdebug[0] != -7 && dbdebug[1] != -7) || (dbdebug[1] != -7 && dbdebug[0] == -7))
	{
		Enemies[_where]->Crash(dbdebug[1], sprdb[1]->Position(), sprdb[1]->TextureSize());
		return true;
	}
	else if (dbdebug[1] == -7 && dbdebug[0] != -7)
	{
		Enemies[_where]->Crash(dbdebug[0], sprdb[0]->Position(), sprdb[0]->TextureSize());
		return true;
	}

	return false;
}

bool MCheckCollapse_Object(int _where)
{
	//아래의 코드는 충돌확인
	//뭐 하나라도 닿으면 바로 true 리턴으로 인한 함수종료가 일어남
	//이하 생략
	for (Sprite* spr : breakableBrick)
	{
			int result = spr->If_Met(Enemies[_where]->RtAn()->Position(), Enemies[_where]->RtAn()->TextureSize());



			if (Enemies[_where]->Crash(result, spr->Position(), spr->TextureSize()))
			{
				if (result == 2)
				{
					breakableBrick.erase(std::find(breakableBrick.begin(), breakableBrick.end(), spr));//삭제
				}
				return true;
			}
	}
	
	return false;
}