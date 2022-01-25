#pragma once
#include "Scene.h"

class Player;

class Sonic : public Scene
{
public:
	Sonic(SceneValues* values);
	~Sonic();

	void Update() override;
	void Render() override;

private:
	void SaveComplete(wstring name);
	void OpenComplete(wstring name);

private:
	Sprite* backGround;

	Player* player;
	vector<class Marker *> markers;
};