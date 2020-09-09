#pragma once
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

class Title;
class Map;
static int face[9] = { cv::FONT_HERSHEY_SIMPLEX, cv::FONT_HERSHEY_PLAIN, cv::FONT_HERSHEY_DUPLEX, cv::FONT_HERSHEY_COMPLEX,
		cv::FONT_HERSHEY_TRIPLEX, cv::FONT_HERSHEY_COMPLEX_SMALL, cv::FONT_HERSHEY_SCRIPT_SIMPLEX,
		cv::FONT_HERSHEY_SCRIPT_COMPLEX, cv::FONT_ITALIC };

class Screen
{
public:
	static const int APLICATION_RUNNING = 0;
	static const int APLICATION_END = 1;
	static const int TITLE_START = 2;
	static const int TITLE_RUNNING = 3;
	static const int GAME_START = 4;
	static const int GAME_RUNNING = 5;
	static const int GAME_RESTART = 6;
	static const int GAME_STAGE_CLEAR = 7;
	static const int GAME_STAGE_CLEARD = 8;
	static const int GAME_CLEAR = 9;
	static const int GAME_OVER = 10;
	static const int GAME_EXIT = 11;

	Screen();
	~Screen();
	int drawScreen();
private:
	Title *m_Title;
	Map	*m_Map;
	int status;
	int stage;
};
