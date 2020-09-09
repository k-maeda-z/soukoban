#pragma once
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Screen.h"
#include "TimeCount.h"
#include "EventAdapter.h"

#define STARTING_TIME	3
#define TIME_MAX	1000

class CharacterManager;

class Map :
	public EventAdapter
{
public:
	Map();
	~Map();
	int drawMap(int stage);
	int ReceiveEvent(int event);
	void receiveGoalEvent();

private:
	CharacterManager *m_CharMng;
	TimeCount* m_TimeCount;
	cv::Mat* m_screenPtr = NULL;
	int	m_CurrentStageNum;
	int m_status;
	int timeCnt;
	int restTime;
	int nowDispRestTime;
	bool switchMoment;
	void resetScreen(bool gameRunning);
};
