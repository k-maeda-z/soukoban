#pragma once
#include "Character.h"
#include "EventAdapter.h"
#include "CharacterManager.h"

class Controlar;

class Player :
    public Character,
	public EventAdapter
{
#define CHARACTER_FILE_PATH	"C://opencv//star.png"
#define OFFSET_X		0
#define OFFSET_Y		0
#define PATTERN_SPEED	3
#define PATTERN_MAX		3

public:
	Player();
	Player(CharacterManager* characterManager);
	void drawCharacter();
	void drawCharacterPosition(int offX, int offY);
	int ReceiveEvent(int event);
	void setCharacterManagerPtr(CharacterManager* ptr);
	void clearCharacter();
	void setMoveAccept(bool accept);

private:
	Controlar* m_controlar;
	CharacterManager* m_characterManager;
	Mat* file = NULL;
	void setImageFile();
	void overlayChar(Mat* src, Mat* dst);
	int move(int direct, int step);
	int step;
	int count;
	int direct;
	bool moveAcceptFlag;
};