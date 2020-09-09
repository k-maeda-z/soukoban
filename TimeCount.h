#pragma once
#include "EventAdapter.h"

class TimeCount
{
public:
	TimeCount(EventAdapter *ptr);
	void operator()();
private:
	EventAdapter* m_eventAdapter;
};

