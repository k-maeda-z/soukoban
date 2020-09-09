#pragma once
#include <stdio.h>
#include <iostream>
#include "mapData.h"
#include "Character.h"
#include "Map.h"

class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();
	static CharacterManager* getInstance();
	void deleteCharacterManager();
	void setCharacter(int stageNum);
	void drawCharactert();
	void setMap(Map* map);
	int getMoveResultPoint(int direct, int step);
	bool isBagGaol();
	void setMoveAccept(bool accept);

private:
	Character* character[CHARACTER_MAX];
	Map* m_map;
	int m_stageNum;
	bool isObstraction(int dircect, position* myPosition, position* othPosition);
	int getMovePoint(int direct, position* myPosition, position* otrPosition, int maxMovePoint);
	int getMovePoint_wall(position* myPosition, int direct, int step, bool bagFlag);
	int getMovePoint_bag(position* mPosition, int direct, int step);
};
