#pragma once
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <list>
#include <string>

using namespace cv;

struct position {
	int id;
	int offsetX;
	int offsetY;
};

class Character {
#define CHARACTER_WIDTH		32
#define CHARACTER_HEIGHT	32
#define REAL_WIDTH		16
#define REAL_HEIGHT		16
public:
	static const int EVENT_IDLE = 0;
	static const int EVENT_UP = 1;
	static const int EVENT_DOWN = 2;
	static const int EVENT_RIGHT = 3;
	static const int EVENT_LEFT = 4;
	std::list<position> lposition;
	Character();
	~Character();
	void addCharacter(int offx, int offy);
	virtual void clearCharacter();
	virtual void drawCharacter();
	virtual void drawCharacterPosition(int offX, int offY);
private:
	int count;
protected:
	Mat* m_screen;
	Mat* character;
	void setImageFile(std::string filePath, int sizeX, int sizeY, int offsetX, int offsetY);
};

