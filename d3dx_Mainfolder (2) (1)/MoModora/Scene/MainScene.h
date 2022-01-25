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

	Sprite* backGround;

	Player* player;

	vector<Friuts> fruitDatabase;

	vector<Line*> lines;

	void CheckLines();

	D3DXVECTOR2 mPos;

	int mapSelect = 0;
};

