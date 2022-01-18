#pragma once
#include "Scene/Scene.h"

class Player;
class Line;

class IceMapScene : public Scene
{
public:
	IceMapScene(SceneValues* values);
	~IceMapScene();

	void Update() override;
	void Render() override;
private:

	Sprite* backGround;

	Player* player;
	vector<Line*> lines;

	void CheckLines();

	D3DXVECTOR2 mPos;

	int mapSelect = 0;
};

