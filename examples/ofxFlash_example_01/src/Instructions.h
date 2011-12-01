/*
 *  Instructions.h
 *  emptyExample
 *
 *  Created by Lukasz Karluk on 10/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashSprite.h"

class Instructions : public ofxFlashSprite
{
	void draw ()
	{
		ofSetColor( 0, 0, 0 );
		ofDrawBitmapString( "drag mouse to move flash logo.", 10, 20 );
		ofDrawBitmapString( "press 'd' to toggle redraw regions.", 10, 40 );
	}
};