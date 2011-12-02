/*
 *  ofxFlashLibraryLoaderIOS.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 9/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class ofxFlashLibraryLoaderIOS
{
	
private: 
	
	static ofxFlashLibraryLoaderIOS* _instance;
	
	 ofxFlashLibraryLoaderIOS() {};
	~ofxFlashLibraryLoaderIOS() {};
	
public:
	
	static ofxFlashLibraryLoaderIOS* getInstance()
	{
		if( !_instance )
		{
			_instance = new ofxFlashLibraryLoaderIOS();
		}
		
        return _instance;
	}
	
	ofBaseDraws* loadImage( string imagePath );
	ofBaseDraws* loadVideo( string videoPath );
	
private:	
	
	bool convertUIImageToOFTexture( void* uiImagePtr, ofTexture &outTexture, int targetWidth = 0, int targetHeight = 0 );
	
};