#pragma once
#include "Object3D.h"

class ReadyGo : public Object3D 
{
public:
	ReadyGo();
	~ReadyGo();
	void Update();
	void Draw();
	/// <summary>
	/// 
	/// </summary>
	/// <returns>Timeが0になったらtrue</returns>
	bool TimeEnd();
private:
	int hReady;
	int hGo;
	float timer;
};