/*
 *  ofxFlashBitmap.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashBitmap.h"

ofxFlashBitmap :: ofxFlashBitmap ( ofImage* image )
{
	bitmapImage = image;
	
	if( bitmapImage != NULL )
	{
		float w = bitmapImage->width;
		float h = bitmapImage->height;
		
		_rect.set_to_rect( 0, 0, w, h );
	}
	
	typeID = OFX_FLASH_BITMAP_TYPE;
}

ofxFlashBitmap :: ~ofxFlashBitmap ()
{
	//
}

///////////////////////////////////////////////
//	RUNTIME METHODS.
///////////////////////////////////////////////

void ofxFlashBitmap :: setup ()
{
	
}

void ofxFlashBitmap :: update ()
{
	//
}

void ofxFlashBitmap :: draw ()
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
		bool bAlpha;
		bAlpha = bitmapImage->type == OF_IMAGE_COLOR_ALPHA;
		
		if( bAlpha )
			ofEnableAlphaBlending();
		
		ofSetColor( 255, 255, 255 );
		
//		bitmapImage->draw( globalX, globalY );
		bitmapImage->draw( 0, 0 );
		
		if( bAlpha )
			ofDisableAlphaBlending();
	}
}
