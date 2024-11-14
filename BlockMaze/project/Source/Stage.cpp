#include "Stage.h"
#include "Player.h"
#include "Coin.h"

//#include�F���̃t�@�C���f�[�^�g���Ă��������ˁI
const int CHIP_SIZE = 40;
#include "stage1.h"

Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");

	//9��T���āAPlayer��u��
	for (int j = 0; j < HIGHT; j++) //�uj�v�c
	{
		for (int i = 0; i < WIDTH; i++)//�ui�v��
		{
			if (map[j][i] == 9)//�v���C���[����
			{
				Player* p = Instantiate<Player>();
				p->position.x = CHIP_SIZE * i + 100;
				p->position.y = CHIP_SIZE * j + 100;
			}
			if (map[j][i] == 2)//�R�C������
			{
				Coin* c = Instantiate<Coin>();
				c->position.x = CHIP_SIZE * i + 100;
				c->position.y = CHIP_SIZE * j + 100;
			}
		}
	}
	scroll = 0;
}

Stage::~Stage()
{
	
}

void Stage::Draw()
{

	//x,y,�؂蔲��,�؂蔲��,40,40
	for (int j = 0; j < HIGHT; j++)		//�c�uj�v
	{
		int y = j * CHIP_SIZE + 100;
		for (int i = 0; i < WIDTH; i++)	//���ui�v
		{
			int x = i * CHIP_SIZE + 100;
			if (map[j][i] == 1)		   //�ԃ����K
			{
				DrawRectGraph(x - scroll, y, CHIP_SIZE * 0, CHIP_SIZE * 1, 40, 40, hImage, TRUE);
			}
			else if (map[j][i] == 8)   //�S�[��
			{
				DrawRectGraph(x - scroll, y, CHIP_SIZE*4, CHIP_SIZE*0, 40, 40, hImage, TRUE);
			}
		}
	}


}

int Stage::IsWallRight(VECTOR2 pos)//pos�ɂ�player���W������
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = ((int)pos.x - 100) % 40 + 1;//0�Ȃ�1 1�Ȃ�2
		return push;
	}
	return 0;
}

int Stage::IsWallLeft(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = 40 - ((int)pos.x - 100) % 40;//39�Ȃ�1 38�Ȃ�2
		return push;
	}
	return 0;
}

int Stage::IsWallDown(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = ((int)pos.y - 100) % 40 + 1;
		return push;
	}
	return 0;
}

int Stage::IsWallUp(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = 40 - ((int)pos.y - 100) % 40;//39�Ȃ�1 38�Ȃ�2
		return push;
	}
	return 0;
}

bool Stage::IsGoal(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 8)
	{
		return true;
	}
	return false;
}
