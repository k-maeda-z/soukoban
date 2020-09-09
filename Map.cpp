#include "Map.h"
#include "CharacterManager.h"
#include "Display.h"


Map::Map() {
	std::cout << "Create Map\n";
	m_screenPtr = (Display::getInstance())->getDisplayScreen();
	m_CharMng = CharacterManager::getInstance();
	m_CharMng->setMap(this);
	m_TimeCount = new TimeCount(this);
	m_CurrentStageNum = 0xff;
	m_status = Screen::GAME_START;
	std::thread th_a(*m_TimeCount);
	th_a.detach();
	switchMoment = true;
}

Map::~Map() {
	std::cout << "Delete Map\n";
}

int Map::drawMap(int stage) {
	int key = 0;
	int status = Screen::GAME_RUNNING;
	char buffer[50];

	if (m_CurrentStageNum != stage) {
		m_CurrentStageNum = stage;
		m_CharMng->deleteCharacterManager();
		m_CharMng->setCharacter(stage);
		m_status = Screen::GAME_START;
	}
	if (m_status == Screen::GAME_START) {
		if (switchMoment == true) {
			// âÊñ êÿÇËë÷ÇÌÇËéûÇÕèâä˙âª
			resetScreen(false);
			if (MAP_MAX > stage) {
				m_CharMng->setCharacter(stage);
			}
		}
		else {
			if (timeCnt < STARTING_TIME) {
				if (MAP_MAX > stage) {
					sprintf_s(buffer, "ROUND %d START !!!", (stage + 1));
					putText(*m_screenPtr, buffer, cv::Point(CHARACTER_WIDTH * 10, CHARACTER_HEIGHT * 10), face[2], 1.2, cv::Scalar(0, 255, 0), 2);
				}
				else {
					putText(*m_screenPtr, "CONGRATULATION STAGE ALL CLEAR !!!", cv::Point(CHARACTER_WIDTH * 3, CHARACTER_HEIGHT * 10), face[2], 1.2, cv::Scalar(0, 255, 0), 2);
				}
			}
			else {
				if (MAP_MAX == stage) {
					return Screen::APLICATION_END;
				}
				else {
					m_status = Screen::GAME_RUNNING;
					// âÊñ êÿÇËë÷ÇÌÇËéûÇÕèâä˙âª
					resetScreen(true);
				}
			}
		}
	}
	else if (m_status == Screen::GAME_RESTART) {
		m_CharMng->deleteCharacterManager();
		m_CharMng->setCharacter(stage);
		m_status = Screen::GAME_RUNNING;
	}
	else if ((m_status == Screen::GAME_RUNNING) || (m_status == Screen::GAME_STAGE_CLEAR)) {
		m_CharMng->drawCharactert();
		putText(*m_screenPtr, "[SPACE]  Retry   [x] Game End        TIME", cv::Point(CHARACTER_WIDTH * 2, CHARACTER_HEIGHT * 19), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
		sprintf_s(buffer, "%d", restTime);
		putText(*m_screenPtr, buffer, cv::Point(CHARACTER_WIDTH * 20, CHARACTER_HEIGHT * 19), face[2], 0.7, cv::Scalar(255, 255, 255), 1);
		if (nowDispRestTime != restTime) {
			sprintf_s(buffer, "%d", nowDispRestTime);
			putText(*m_screenPtr, buffer, cv::Point(CHARACTER_WIDTH * 20, CHARACTER_HEIGHT * 19), face[2], 0.7, cv::Scalar(0, 0, 0), 1);
			nowDispRestTime = restTime;
		}
		sprintf_s(buffer, "%d", restTime);
		putText(*m_screenPtr, buffer, cv::Point(CHARACTER_WIDTH * 20, CHARACTER_HEIGHT * 19), face[2], 0.7, cv::Scalar(255, 255, 255), 1);

		if (m_status == Screen::GAME_STAGE_CLEAR) {
			m_status = Screen::GAME_STAGE_CLEARD;
		}
	}
	else if (m_status == Screen::GAME_OVER) {
		if (switchMoment == true) {
			// âÊñ êÿÇËë÷ÇÌÇËéûÇÕèâä˙âª
			resetScreen(false);
		}
		else {
			if (timeCnt < STARTING_TIME) {
				putText(*m_screenPtr, "TIME OVER", cv::Point(CHARACTER_WIDTH * 13, CHARACTER_HEIGHT * 8), face[2], 1.2, cv::Scalar(0, 255, 0), 2);
				sprintf_s(buffer, "GAME OVER ROUND %d", (stage + 1));
				putText(*m_screenPtr, buffer, cv::Point(CHARACTER_WIDTH * 10, CHARACTER_HEIGHT * 10), face[2], 1.2, cv::Scalar(0, 255, 0), 2);
			}
			else {
				switchMoment = true;
				m_status = Screen::GAME_START;
				return Screen::GAME_EXIT;
			}
		}
	}
	else if (m_status == Screen::GAME_STAGE_CLEARD) {
		if (switchMoment == true) {
			// âÊñ êÿÇËë÷ÇÌÇËéûÇÕèâä˙âª
			resetScreen(false);
		}
		else {
			if (timeCnt < STARTING_TIME) {
				sprintf_s(buffer, "STAGE CLEAR ROUND %d", (stage + 1));
				putText(*m_screenPtr, buffer, cv::Point(CHARACTER_WIDTH * 10, CHARACTER_HEIGHT * 8), face[2], 1.2, cv::Scalar(0, 255, 0), 2);
				putText(*m_screenPtr, "GO TO NEXT STAGE !!!", cv::Point(CHARACTER_WIDTH * 10, CHARACTER_HEIGHT * 11), face[2], 1.2, cv::Scalar(0, 255, 0), 2);
			}
			else {
				m_status = Screen::GAME_START;
				switchMoment = true;
				return Screen::GAME_STAGE_CLEAR;
			}
		}
	}

	imshow("SCREEN", *m_screenPtr);
	key = waitKey(10);
	if ((m_status == Screen::GAME_RUNNING) && (key == ' ')) {
		m_status = Screen::GAME_RESTART;
	}
	else if (key == 'x') {
		return Screen::APLICATION_END;
	}

	return Screen::GAME_RUNNING;
}

int Map::ReceiveEvent(int event) {
	if ((m_status == Screen::GAME_RUNNING) && (restTime >= 0)) {
		restTime--;
		if (restTime <= 0) {
			m_status = Screen::GAME_OVER;
			restTime = 0;
			switchMoment = true;
		}
	}
	timeCnt++;

	return 0;
}

void Map::receiveGoalEvent() {
	m_status = Screen::GAME_STAGE_CLEAR;
	m_CharMng->setMoveAccept(false);
	switchMoment = true;
}

void Map::resetScreen(bool gameRunning) {
	// âÊñ êÿÇËë÷ÇÌÇËéûÇÕèâä˙âª
	(Display::getInstance())->initDisplayScreen();
	m_screenPtr = (Display::getInstance())->getDisplayScreen();
	timeCnt = 0;
	if (gameRunning == true) {
		m_CharMng->setMoveAccept(true);
		restTime = TIME_MAX;
	}
	else {
		switchMoment = false;
		m_CharMng->setMoveAccept(false);
		m_CharMng->deleteCharacterManager();
	}
}

