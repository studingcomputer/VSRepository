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

	void CheckLines();


	//�̸� �������� ���� �ϳ�
	D3DXVECTOR2 a = D3DXVECTOR2(-100, 100);
	D3DXVECTOR2 b = D3DXVECTOR2(0, 100);
};