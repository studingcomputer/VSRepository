#pragma once
#include "Scene.h"

class Player;

class Stage1 : public Scene
{
public:
	Stage1(SceneValues* values);
	~Stage1();

	void Update() override;
	void Render() override;

private:
	Sprite* backGround;

	Player* player;
};