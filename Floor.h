#pragma once
#include "Character.h"

class Floor :
	public Character
{
#define CHARACTER_FILE_PATH	"C://opencv//map.png"
#define OFFSET_X		1
#define OFFSET_Y		4

public:
	Floor();
};

