/*
 *  Cross.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 21/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxFlash.h"

class Cross : public ofxFlashSprite
{
	
public:
	
	Cross()
	{
		//
	};
	
	~Cross()
	{
		//
	}
	
	void draw ()
	{
		ofNoFill();
		ofSetColor( 0, 255, 255 );
		ofLine( ofGetWidth() * 0.5, 0, ofGetWidth() * 0.5, ofGetHeight() );
		ofLine( 0, ofGetHeight() * 0.5, ofGetWidth(), ofGetHeight() * 0.5 );
	}
};