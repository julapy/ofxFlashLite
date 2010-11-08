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

#define OFX_FLASH_STAGE_TYPE						0
#define OFX_FLASH_MOVIE_CLIP_TYPE					1
#define OFX_FLASH_SPRITE_TYPE						2
#define OFX_FLASH_DISPLAY_OBJECT_CONTAINER_TYPE		3
#define OFX_FLASH_INTERACTIVE_OBJECT_TYPE			4
#define OFX_FLASH_BITMAP_TYPE						5
#define OFX_FLASH_DISPLAY_OBJECT_TYPE				6
#define OFX_FLASH_EVENT_DISPATCHER_TYPE				7
#define OFX_FLASH_OBJECT_TYPE						8

class ofxFlashObject
{
	
public:

	 ofxFlashObject();
	~ofxFlashObject();
	
	int typeID;
	
};