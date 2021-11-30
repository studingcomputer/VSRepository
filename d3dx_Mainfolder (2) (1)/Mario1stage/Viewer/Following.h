#pragma once
#include "IFollowing.h"
#include "Camara.h"

class Following : public Camara
{
public:
	Following(IFollowing* focus = NULL);
	~Following();

	void Change(IFollowing* focus);
	void Update();

	D3DXVECTOR2 Position() { return position; }
private:

	IFollowing* focus;
};