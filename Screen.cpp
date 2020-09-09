#include "Screen.h"
#include "Title.h"
#include "Map.h"

Screen::Screen() {
	status = Screen::TITLE_START;
	m_Title = new Title();
	m_Map = new Map();
	stage = 0;
}

Screen::~Screen() {
	delete(m_Title);
	delete(m_Map);
}

int Screen::drawScreen() {
	if ((status == Screen::TITLE_RUNNING) || (status == Screen::TITLE_START)) {
		status = m_Title->drawTitle();
	} else {
		status = m_Map->drawMap(stage);
		if (status == Screen::GAME_STAGE_CLEAR) {
			stage++;
			status = Screen::GAME_RUNNING;
		}
		else if (status == Screen::GAME_EXIT) {
			stage = 0;
			status = Screen::TITLE_START;
		}
	}

	if (status == Screen::APLICATION_END) {
		return Screen::APLICATION_END;
	}

	return Screen::APLICATION_RUNNING;
}
