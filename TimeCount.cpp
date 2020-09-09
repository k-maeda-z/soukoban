#include "TimeCount.h"
#include <stdio.h>
#include <iostream>
#include <thread>

TimeCount::TimeCount(EventAdapter* ptr) {
    std::cout << "Create TimeCount\n";
    m_eventAdapter = ptr;
}

void TimeCount::operator()() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        m_eventAdapter->ReceiveEvent(EventAdapter::EVENT_1SECOND);
    }
}
