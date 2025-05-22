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
	/// <returns>Time‚ª0‚É‚È‚Á‚½‚çtrue</returns>
	bool TimeEnd();
private:
	int hReady;
	int hGo;
	float timer;
};