#pragma once
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#if 1
#define SCREEN_WIDTH		960
#define SCREEN_HEIGHT		640
#endif
using namespace cv;

class Display
{
public:
	static Display* getInstance();
	Mat* getDisplayScreen();
	void  initDisplayScreen();
	Display();
	~Display();
private:
	Mat m_screen;
	Mat* m_screenPtr = NULL;
};

