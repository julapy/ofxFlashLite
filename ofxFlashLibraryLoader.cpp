/*
 *  ofxFlashLibraryLoader.cpp
 *  iPhoneEmptyExample
 *
 *  Created by lukasz karluk on 10/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashLibraryLoader.h"

#ifndef TARGET_OF_IPHONE

ofxFlashLibraryLoader* ofxFlashLibraryLoader :: _instance = NULL;

ofBaseDraws* ofxFlashLibraryLoader :: loadImage( string imagePath )
{
	ofImage image;
	
	if( !image.loadImage( imagePath ) )
		return NULL;
	
	ofTexture* tex = new ofTexture();
	tex->allocate( image.getWidth(), image.getHeight(), image.getTextureReference().getTextureData().glType );
	tex->loadData( image.getPixels(), image.getWidth(), image.getHeight(), image.getTextureReference().getTextureData().glType );
	
	return tex;
}

ofBaseDraws* ofxFlashLibraryLoader :: loadVideo( string videoPath )
{
	ofVideoPlayer* video = new ofVideoPlayer();
	video->loadMovie( videoPath );
	
	return video;
}

#endif