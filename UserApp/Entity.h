#pragma once
#include "vector.h"
#include "CsgoProcess.h"
#include "Offsets.h"

class Entity
{

public:

	int base_address;
	int health;
	Vector Position;
	char name[32];
	int team;
	bool defusing;
	short weaponid;
	char lastplace[32];

	Entity(ULONG base, int index);

	bool isAlive();
};