#include "Character.h"
#include "Display.h"
#include <string>

using namespace cv;

Character::Character() {
	std::cout << "Create Character\n";
	m_screen = (Display::getInstance())->getDisplayScreen();
	count = 0;
}

Character::~Character() {
	std::cout << "Delete Character\n";
	// リスト要素全消去
	lposition.clear();
}

void Character::clearCharacter() {
	// リスト要素全消去
	lposition.clear();
}

void Character::addCharacter(int offx, int offy) {
	count++;

	position pos;
	pos.id = count;
	pos.offsetX = offx;
	pos.offsetY = offy;
	lposition.push_back(pos);
}

void Character::drawCharacter() {
	auto itr = lposition.begin();
	int size = lposition.size();
	Mat* image_clip = NULL;

	for (int i = 0;i<size;i++) {
		image_clip = new Mat(*m_screen,
			Rect(itr->offsetX, itr->offsetY,
				CHARACTER_WIDTH, CHARACTER_HEIGHT));
		character->copyTo(*image_clip);
		delete(image_clip);
		itr++;
	}
}

void Character::drawCharacterPosition(int offX, int offY) {
	Mat* image_clip = NULL;
	image_clip = new Mat(*m_screen,
		Rect(offX, offY,
			CHARACTER_WIDTH, CHARACTER_HEIGHT));
	character->copyTo(*image_clip);
	delete(image_clip);
}

void Character::setImageFile(std::string filePath, int sizeX, int sizeY, int offsetX, int offsetY) {

	Mat* file = NULL;
	file = new Mat;
	*file = imread(filePath, -1);
	character = new Mat(*file, Rect(sizeX * offsetX, sizeY * offsetY, sizeX, sizeY));
	resize(*character, *character, cv::Size(), CHARACTER_WIDTH / sizeX, CHARACTER_HEIGHT / sizeY);

}



