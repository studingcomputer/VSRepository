#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"


Background* bg;
Player* player;
vector<Sprite*> sprite;
vector<Sprite*> breakableBrick;
vector<Sprite*> brick_Query;
Sprite* anEntrence;
vector<Sprite*> floor_;
Camara* freeCam;

bool CheckCollapse_floor();
bool CheckCollapse_Object();

int res_debug;
int deadcount = 0;

void InitScene()
{

	bg = new Background(Shaders + L"/009_Sprite.fx");
	bg->Scale(D3DXVECTOR2(2.5f, 2.5f));
	bg->Position(D3DXVECTOR2(4220, 0));
	player = new Player(D3DXVECTOR2(100, 120), D3DXVECTOR2(0.8f, 0.8f));


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
		sprite.back()->Position(1304 * 2.5, 88 * 4.5);
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
}

D3DXMATRIX V, P;
void Update()
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
	//for (Sprite* spr : brick_Query)
	//	spr->Update(freeCam->View(), P);
	//anEntrence->Update(freeCam->View(), P);
	for (Sprite* spr : floor_)
		spr->Update(freeCam->View(), P);


	if (!CheckCollapse_floor())
		CheckCollapse_Object();

	player->UpdatePos();

	player->Update(freeCam->View(), P);

	if (player->IsDead())
	{
		//죽었을 때 처리
		MessageBox(NULL, L"플레이어가 죽었습니다", L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
		MessageBox(NULL, L"플레이어가 죽었습니다.", L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
		MessageBox(NULL, L"플레이어가 죽었다고.", L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
		MessageBox(NULL, L"죄책감조차 못 느끼는 거야?", L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
		MessageBox(NULL, L"네가 초래한 일이야.", L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
		if (deadcount++ > 0)
		{
			wstring s = L"벌써 이 캐릭터는 " + to_wstring(deadcount) + L"번이나 죽어버렸어.";
			LPCWSTR message = (LPCWSTR)s.c_str();
			MessageBox(NULL, message, L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
			if (deadcount == 10)
			{
				MessageBox(NULL, L"차라리, 이 세계를 부숴야겠어.", L"Yo▦ Ki▦Le▦ H▦m", MB_OK);
				DestroyScene();
				return;
			}
		}

		DestroyScene();
		InitScene();
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

		//for (Sprite* spr : brick_Query)
		//	spr->Render();

		//anEntrence->Render();

		for (Sprite* spr : floor_)
			spr->Render();
		/*-----------debug--------------
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
		-----------debug--------------*/
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
				dbdebug[0] = res_debug;
				sprdb[0] = spr;
				break;
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

			if (result == 2)
			{
				breakableBrick.erase(std::find(breakableBrick.begin(), breakableBrick.end(), spr));//삭제
			}

			if (player->Crash(result, spr->Position(), spr->TextureSize()))
				return true;
		}
	}
	/*for (Sprite* spr : brick_Query)
	{
		if (!(
			(spr->Position().x - spr->TextureSize().x * 0.5f > freeCam->Position().x + Width) ||
			(spr->Position().x + spr->TextureSize().x * 0.5f < freeCam->Position().x)
			))
		{
			if (player->Crash(spr->If_Met(player->RtAn()->Position(), player->RtAn()->TextureSize()), spr->Position(), spr->TextureSize()))
				return true;
		}
	}
	if (!(
		(anEntrence->Position().x - anEntrence->TextureSize().x * 0.5f > freeCam->Position().x + Width) ||
		(anEntrence->Position().x + anEntrence->TextureSize().x * 0.5f < freeCam->Position().x)
		))
	{
		if (player->Crash(anEntrence->If_Met(player->RtAn()->Position(), player->RtAn()->TextureSize()), anEntrence->Position(), anEntrence->TextureSize()))
			return true;
	}*/
	return false;
}