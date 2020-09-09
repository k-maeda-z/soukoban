#include "Controlar.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <windows.h>



//Controlar::Controlar(Player *player) {
Controlar::Controlar(EventAdapter *eventAdapter) {
    std::cout << "Create Controlar\n";
    m_EventAdapter = eventAdapter;
    m_direct = EventAdapter::EVENT_DOWN;
    repeatCnt = 0;
}

void Controlar::operator()() {
    std::cout << "operator Controlar\n";
    while (true) {
        Sleep(50);
        inputKeyEvent();
    }
}

void Controlar::inputKeyEvent() {
    int key = 0;
    bool flag = false;
    int movePoint = 0;

    if (repeatCnt == 0) {
        m_direct = DIRECT_IDLE;
        if (GetKeyState(VK_NUMPAD2) < 0) {
            m_direct = EventAdapter::EVENT_DOWN;
        }
        else if (GetKeyState(VK_NUMPAD4) < 0) {
            m_direct = EventAdapter::EVENT_LEFT;
        }
        else if (GetKeyState(VK_NUMPAD6) < 0) {
            m_direct = EventAdapter::EVENT_RIGHT;
        }
        else if (GetKeyState(VK_NUMPAD8) < 0) {
            m_direct = EventAdapter::EVENT_UP;
        }
    }

    if (m_direct != DIRECT_IDLE) {
        movePoint = m_EventAdapter->ReceiveEvent(m_direct);
        // 進めない時はキー受付可にする
        if (movePoint == 0) {
            repeatCnt = 0;
        }
        else if ((repeatCnt + 1) == REPEAT_CNT_MAX) {
            repeatCnt = 0;
        }
        else {
            repeatCnt++;
        }
    }
}

