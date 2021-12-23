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


	//�̸� �������� ���� �ϳ�
	D3DXVECTOR2 a = D3DXVECTOR2(-100, 0);
	D3DXVECTOR2 b = D3DXVECTOR2(0, 0);
};