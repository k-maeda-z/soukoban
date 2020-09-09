#include "Wall.h"

Wall::Wall() {
	std::cout << "Create Wall\n";
	Character::setImageFile(CHARACTER_FILE_PATH, REAL_WIDTH, REAL_HEIGHT, OFFSET_X, OFFSET_Y);
}

