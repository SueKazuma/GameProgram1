#pragma once

//const:書き換えられない定数
//直接数字を書くと人格否定される
//数字ではなく文字で書く
const int WIDTH = 30;
const int HIGHT = 8;

int map[HIGHT][WIDTH] =
{
	//30			   10				   20				   30				   40				   50				   60				   70
  // 1,2.3.4.5.6.7.8.9.0,1,2.3.4.5.6.7.8.9.0,1,2.3.4.5.6.7.8.9.0,1,2.3.4.5.6.7.8.9.0,1,2.3.4.5.6.7.8.9.0,1,2.3.4.5.6.7.8.9.0,1,2.3.4.5.6.7.8.9.0,}
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{1,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
	{1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{1,2,2,2,1,0,1,1,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,9,0,0,8,0,0,},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,} 
};

//０：Empty
//１：ブロック
//８：ゴール
//９：プレイヤー
