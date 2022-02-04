#pragma once
#include "Scene/Scene.h"
#include <thread>

class Player;
class Line;
class Friuts;
class Bullet;

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

	static void UpdateThread1(MainScene* main);
	static void UpdateThread2(MainScene* main);
	static void UpdateThread3(MainScene* main);

	Sprite* backGround[3];

	Player* player;

	vector<Friuts*> fruitDatabase;
	vector<Sprite*> blocks;
	vector<Line*> lines;
	vector<Bullet*> Bullets;

	void CheckLines();

	D3DXVECTOR2 mPos;

	vector<thread> threads;

	int mapSelect = 0;

	bool isPlay = false;
};

