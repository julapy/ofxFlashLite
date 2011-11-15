/*
 *  ofxFlashObject.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

enum ofxFlashObjectType
{
    OFX_FLASH_TYPE_STAGE                    = 0,
    OFX_FLASH_TYPE_MOVIECLIP                = 1,
    OFX_FLASH_TYPE_SPRITE                   = 2,
    OFX_FLASH_TYPE_DISPLAY_OBJECT_CONTAINER = 3,
    OFX_FLASH_TYPE_INTERACTIVE_OBJECT       = 4,
    OFX_FLASH_TYPE_BITMAP                   = 5,
    OFX_FLASH_TYPE_SHAPE                    = 6,
    OFX_FLASH_TYPE_DISPLAY_OBJECT           = 7,
    OFX_FLASH_TYPE_EVENT_DISPATCHER         = 8,
    OFX_FLASH_TYPE_OBJECT                   = 9
};

class ofxFlashObject
{
	
public:

	 ofxFlashObject();
	~ofxFlashObject();
	
	ofxFlashObjectType typeID;
	
};