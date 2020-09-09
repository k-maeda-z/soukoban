#include "Goal.h"

Goal::Goal() {
	std::cout << "Create Goal\n";
	Character::setImageFile(CHARACTER_FILE_PATH, REAL_WIDTH, REAL_HEIGHT, OFFSET_X, OFFSET_Y);
}

