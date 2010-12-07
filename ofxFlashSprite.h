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
	
	virtual void setup	() {};
	virtual void update	() {};
	virtual void draw	() {};
	
protected:
	
	virtual void updateOnFrame () {};
	
private:
	
	bool					_buttonMode;
	ofxFlashDisplayObject*	_dropTarget;
	ofxFlashSprite*			_hitArea;
	bool					_useHandCursor;
	
	// TODO :: graphics
	// TODO :: soundTransform
	
};