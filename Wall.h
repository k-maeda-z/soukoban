#pragma once
#include "Character.h"
class Wall :
    public Character
{
#define CHARACTER_FILE_PATH	"C://opencv//map.png"
#define OFFSET_X		0
#define OFFSET_Y		30

public:
	Wall();
};

