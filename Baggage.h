#pragma once
#include "Character.h"
#include "CharacterManager.h"

class Baggage :
    public Character
{
#define CHARACTER_FILE_PATH	"C://opencv//map.png"
#define OFFSET_X		2
#define OFFSET_Y		30

public:
	Baggage();
	Baggage(CharacterManager* characterManager);
	void move(int id, int direct, int step);
private:
	CharacterManager* m_characterManager;
};

