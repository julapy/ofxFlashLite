/*
 *  ofxFlashLibraryGeneric.h
 *  iPhoneEmptyExample
 *
 *  Created by lukasz karluk on 10/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class ofxFlashLibraryLoader
{
	
private: 
	
	static ofxFlashLibraryLoader* _instance;
	
	 ofxFlashLibraryLoader() {};
	~ofxFlashLibraryLoader() {};
	
public:
	
	static ofxFlashLibraryLoader* getInstance()
	{
		if( !_instance )
		{
			_instance = new ofxFlashLibraryLoader();
		}
		
        return _instance;
	}
	
	ofBaseDraws* loadImage( string imagePath );
	ofBaseDraws* loadVideo( string videoPath );
	
};