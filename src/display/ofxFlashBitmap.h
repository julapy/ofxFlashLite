/*
 *  ofxFlashBitmap.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashDisplayObject.h"

class ofxFlashBitmap : public ofxFlashDisplayObject
{
	
public:
	
	 ofxFlashBitmap( ofBaseDraws* image );
	~ofxFlashBitmap();
	
	//-------------------------------------------
	
	ofBaseDraws*	bitmapImage;
	
	//-------------------------------------------
	
	virtual void setup	() {};
	virtual void update	() {};
	virtual void draw	() {};
	
protected:
	
	virtual void updateOnFrame	();
	virtual void drawOnFrame	();
	
private:
	
	void drawBitmap	();
	
};