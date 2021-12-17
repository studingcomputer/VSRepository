#pragma once
#include "Scene/Scene.h"

class Player;
class Line;

class Sonic : public Scene
{
public:
	Sonic(SceneValues* values);
	~Sonic();

	void Update() override;
	void Render() override;
private:

	Sprite* backGround;

	Player* player;
	vector<class Marker*> markers;
	vector<Line*> lines;
};