#include "Floor.h"

Floor::Floor() {
	std::cout << "Create Floor\n";
	Character::setImageFile(CHARACTER_FILE_PATH, REAL_WIDTH, REAL_HEIGHT, OFFSET_X, OFFSET_Y);
}

