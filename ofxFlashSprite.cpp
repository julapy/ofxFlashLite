/*
 *  ofxFlashSprite.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashSprite.h"

ofxFlashSprite :: ofxFlashSprite()
{
	typeID = OFX_FLASH_TYPE_SPRITE;
	
	_buttonMode		= false;
	_dropTarget		= NULL;
	_hitArea		= NULL;
	_useHandCursor	= false;
}

ofxFlashSprite :: ~ofxFlashSprite()
{

}