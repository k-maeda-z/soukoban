#include "Display.h"

using namespace cv;

Display::Display() {
	std::cout << "Create Display\n";
	// スクリーン全体を黒で表示
	m_screen = Mat::zeros(SCREEN_HEIGHT, SCREEN_WIDTH, CV_8UC4);
	m_screenPtr = &m_screen;
}

Display::~Display() {
	std::cout << "Delete Display\n";
}

Display* Display::getInstance() {
	static Display instance;
	return &instance;
}

void Display::initDisplayScreen() {
	if (m_screenPtr != NULL) {
		m_screenPtr->release();
	}
	m_screen = Mat::zeros(SCREEN_HEIGHT, SCREEN_WIDTH, CV_8UC4);
	m_screenPtr = &m_screen;
}

Mat* Display::getDisplayScreen() {
	return m_screenPtr;
}


