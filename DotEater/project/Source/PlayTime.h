#pragma once
#include "Object3D.h"
class PlayTime : public Object3D
{
public:
	PlayTime();
	~PlayTime();
	void Update();
	void Draw();
	/// <summary>
	/// 
	/// </summary>
	/// <returns>Time��0�ɂȂ�����true</returns>
	bool TimeUp();
private:
	float timer;
};

