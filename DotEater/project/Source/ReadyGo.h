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
	/// <returns>Time��0�ɂȂ�����true</returns>
	bool TimeEnd();
private:
	int hReady;
	int hGo;
	float timer;
};