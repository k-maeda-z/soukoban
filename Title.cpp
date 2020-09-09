#include "Title.h"
#include "Display.h"
#include "Floor.h"
#include "Wall.h"
#include "Baggage.h"
#include "Goal.h"
#include "Player.h"

using namespace cv;

Title::Title() {
    m_screenPtr = (Display::getInstance())->getDisplayScreen();
    m_status = Screen::TITLE_START;
}

Title::~Title() {
	std::cout << "Delete Title\n";
}

int Title::drawTitle() {
    Mat* image_clip = NULL;
    Floor floor;
    Wall wall;
    Baggage baggage;
    Goal goal;
    Player player;
    int key = 0;
    int status = m_status;

    if (m_status == Screen::TITLE_START) {
        // 画面切り替わり時は初期化
        (Display::getInstance())->initDisplayScreen();
        m_screenPtr = (Display::getInstance())->getDisplayScreen();
    }

    // スクリーン全体を黒で表示
    putText(*m_screenPtr, "                      *------- SOUKOBAN -------*", cv::Point(50, 50), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    putText(*m_screenPtr, "                [8] DOWN", cv::Point(50, 150), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    putText(*m_screenPtr, "    [4] LEFT                 [6] RIGHT", cv::Point(50, 250), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    putText(*m_screenPtr, "                [2] DOWN", cv::Point(50, 350), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    putText(*m_screenPtr, " [z]      Game Start", cv::Point(50, 550), face[2], 0.7, cv::Scalar(0, 255, 0), 1);
    putText(*m_screenPtr, " [x]      Game End", cv::Point(50, 600), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    putText(*m_screenPtr, ": PLAYER", cv::Point(CHARACTER_WIDTH * 20, CHARACTER_HEIGHT * 6), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    player.drawCharacterPosition(CHARACTER_WIDTH * 18, CHARACTER_HEIGHT * 5);
    putText(*m_screenPtr, ": FLOOR", cv::Point(CHARACTER_WIDTH * 20, CHARACTER_HEIGHT * 8), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    floor.drawCharacterPosition(CHARACTER_WIDTH * 18, CHARACTER_HEIGHT * 7);
    putText(*m_screenPtr, ": WALL", cv::Point(CHARACTER_WIDTH * 20, CHARACTER_HEIGHT * 10), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    wall.drawCharacterPosition(CHARACTER_WIDTH * 18, CHARACTER_HEIGHT * 9);
    putText(*m_screenPtr, ": BAG", cv::Point(CHARACTER_WIDTH * 20, CHARACTER_HEIGHT * 12), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    baggage.drawCharacterPosition(CHARACTER_WIDTH * 18, CHARACTER_HEIGHT * 11);
    putText(*m_screenPtr, ": GOAL", cv::Point(CHARACTER_WIDTH * 20, CHARACTER_HEIGHT * 14), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
    goal.drawCharacterPosition(CHARACTER_WIDTH * 18, CHARACTER_HEIGHT * 13);
    imshow("SCREEN", *m_screenPtr);
    key = waitKey(0);
    if (key == 'z') {
        status = Screen::GAME_START;
        m_status = Screen::TITLE_START;
    }
    else if (key == 'x') {
        status = Screen::APLICATION_END;
    }
    else {
        status = m_status = Screen::TITLE_RUNNING;
    }

    return status;
}