//-----------------------------------------------------------------
// Character Object
// C++ Source - Character.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Character.h"

//-----------------------------------------------------------------
// Character Constructor(s)/Destructor
//-----------------------------------------------------------------
Character::Character(std::string _name, std::string _description, Sprite* _sprite, int _healthPoint, int _speed, POINT _mapPosition) {
	name = _name;
	description = _description;
	sprite = _sprite;
	speed = _speed;
	healthPoint = _healthPoint;
	maxHealthPoint = _healthPoint;
	mapPosition = _mapPosition;
}

Character::~Character()
{
}


//-----------------------------------------------------------------
// Character General Methods
//-----------------------------------------------------------------
