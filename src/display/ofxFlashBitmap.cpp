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
    typeID = OFX_FLASH_TYPE_BITMAP;
    
	bitmapImage = image;
	
	if( bitmapImage != NULL )
	{
		float w = bitmapImage->getWidth();
		float h = bitmapImage->getHeight();
		
        width( w );
        height( h );
	}
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
