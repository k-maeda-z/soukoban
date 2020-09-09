#pragma once
#include "EventAdapter.h"

#define DIRECT_IDLE		0
#define DIRECT_UP		1
#define DIRECT_RIGHT	2
#define DIRECT_DOWN		3
#define DIRECT_LEFT		4

#define REPEAT_CNT_MAX	8

class Controlar
{
public:
	Controlar(EventAdapter *eventAdapter);
	void operator()();

private:
	EventAdapter *m_EventAdapter;
	int m_direct;
	int repeatCnt;
	void inputKeyEvent();
};

