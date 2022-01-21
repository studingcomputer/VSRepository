#pragma once
#include "Scene/Scene.h"

class Player;
class Line;

class SunSetMap : public Scene
{
public:
	SunSetMap(SceneValues* values);
	~SunSetMap();

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

