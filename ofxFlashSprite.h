/*
 *  ofxFlashSprite.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashDisplayObjectContainer.h"

class ofxFlashSprite : public ofxFlashDisplayObjectContainer
{

public:
	
	 ofxFlashSprite();
	~ofxFlashSprite();
	
	//======================================= INTERNAL METHODS - these methods are to be used by ofxFlash only.
	
	virtual void updateInternal	() {};
	
	//======================================= INTERNAL METHODS - these methods are to be used by ofxFlash only.
	
	virtual void setup	();
	virtual void update	();
	virtual void draw	();
	
};