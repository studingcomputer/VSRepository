#pragma once
#include "Scene/Scene.h"

class Player;
class Line;
class Friuts;

class MainScene : public Scene
{
public:
	MainScene(SceneValues* values);
	~MainScene();

	void Update() override;
	void Render() override;
private:
	
	void SaveComplete(wstring name);
	void OpenComplete(wstring name);

	void Reset_Process();

	Sprite* backGround[3];

	Player* player;

	vector<Friuts*> fruitDatabase;

	vector<Sprite*> blocks;
	
	vector<Line*> lines;

	void CheckLines();

	D3DXVECTOR2 mPos;

	int mapSelect = 0;

	bool isPlay = false;
};

