/*
 *  ofxFlashBitmap.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashBitmap.h"

ofxFlashBitmap :: ofxFlashBitmap ( ofBaseDraws* image )
{
	bitmapImage = image;
	
	if( bitmapImage != NULL )
	{
		float w = bitmapImage->getWidth();
		float h = bitmapImage->getHeight();
		
		_rect.set_to_rect( 0, 0, w, h );
	}
	
	typeID = OFX_FLASH_BITMAP_TYPE;
}

ofxFlashBitmap :: ~ofxFlashBitmap ()
{
	bitmapImage = NULL;     // don't delete bitmapImage as its managed by ofxFlashLibrary.
}

///////////////////////////////////////////////
//
///////////////////////////////////////////////

void ofxFlashBitmap :: updateOnFrame ()
{
	
}

void ofxFlashBitmap :: drawOnFrame ()
{
	drawBitmap();
}

///////////////////////////////////////////////
//
///////////////////////////////////////////////

void ofxFlashBitmap :: drawBitmap ()
{
	if( bitmapImage != NULL )
	{
		float a = compoundAlpha();

		ofSetColor( 255, 255, 255, a * 255 );
		
		bitmapImage->draw( 0, 0 );
	}
}
