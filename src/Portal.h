//-----------------------------------------------------------------
// Wall Sprite Object
// C++ Header - WallSprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Sprite.h"

//-----------------------------------------------------------------
// WallSprite Class
//-----------------------------------------------------------------
class Portal : public Sprite
{
public:
	// Constructor(s)/Destructor
	Portal(Bitmap* _bitmap);
	virtual ~Portal();
	bool isReady;

};
#pragma once
