#pragma once
#include "Scene.h"

class Stage2 : public Scene
{
public:
	Stage2(SceneValues* values);
	~Stage2();

	void Update() override;
	void Render() override;

private:
	void RenderBackground();

private:
	Sprite* backGrounds[3];

	class Player* player;
	class Bullet* bullet;
	class Fire* fire;

	bool check;
};