#pragma once
class EventAdapter
{
public:
	static const int EVENT_IDLE  = 0;
	static const int EVENT_UP    = 1;
	static const int EVENT_DOWN  = 2;
	static const int EVENT_RIGHT = 3;
	static const int EVENT_LEFT = 4;
	static const int EVENT_1SECOND = 5;
	EventAdapter();
	virtual int ReceiveEvent(int event) = 0;
};

