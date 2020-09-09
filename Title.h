#pragma once
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Screen.h"

class Display;
using namespace cv;

class Title
{
public:
	Title();
	~Title();
	int drawTitle();

private:
	Display* m_display;
	cv::Mat* m_screenPtr = NULL;
	int m_status;
};
