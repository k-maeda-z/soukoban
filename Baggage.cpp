#include "Baggage.h"

Baggage::Baggage() {
	std::cout << "Create Baggage\n";
	Character::setImageFile(CHARACTER_FILE_PATH, REAL_WIDTH, REAL_HEIGHT, OFFSET_X, OFFSET_Y);
}

Baggage::Baggage(CharacterManager* characterManager) {
	std::cout << "Create Baggage (CharacterManager*)\n";
	Character::setImageFile(CHARACTER_FILE_PATH, REAL_WIDTH, REAL_HEIGHT, OFFSET_X, OFFSET_Y);
	m_characterManager = characterManager;
}

void Baggage::move(int id, int direct, int step) {

	auto bagItr = this->lposition.begin();
	int bagSize = this->lposition.size();

	for (int i = 0;i < bagSize;i++) {
		if (bagItr->id == id) {
			switch (direct) {
				case Character::EVENT_UP:
					bagItr->offsetY -= step;
					break;
				case Character::EVENT_DOWN:
					bagItr->offsetY += step;
					break;
				case Character::EVENT_RIGHT:
					bagItr->offsetX += step;
					break;
				case Character::EVENT_LEFT:
					bagItr->offsetX -= step;
					break;
				default:
					break;
			}
			break;
		}
		bagItr++;
	}

	if (m_characterManager->isBagGaol() == true) {
		std::cout << "move Baggage Gaol\n";
	}
}

