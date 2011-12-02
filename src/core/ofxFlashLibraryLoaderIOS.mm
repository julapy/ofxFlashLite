/*
 *  ofxFlashLibraryLoaderIOS.mm
 *  emptyExample
 *
 *  Created by lukasz karluk on 9/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashLibraryLoaderIOS.h"

#ifdef TARGET_OF_IPHONE

#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

ofxFlashLibraryLoaderIOS* ofxFlashLibraryLoaderIOS :: _instance = NULL;

ofBaseDraws* ofxFlashLibraryLoaderIOS :: loadImage( string path )
{
	NSString*	imagePath;
	UIImage*	image;
	
	imagePath	= ofxStringToNSString( ofToDataPath( path ) );
	image		= [ [ UIImage alloc ] initWithContentsOfFile : imagePath ];

	ofTexture* tex = new ofTexture();
	
	convertUIImageToOFTexture( image, *tex );
	
	[ image release ];
	
	return tex;
}

ofBaseDraws* ofxFlashLibraryLoaderIOS :: loadVideo( string videoPath )
{
	return NULL;
}

/////////////////////////////////////////////
//	CONVERTION.
/////////////////////////////////////////////

bool ofxFlashLibraryLoaderIOS :: convertUIImageToOFTexture( void* uiImagePtr, ofTexture &outTexture, int targetWidth, int targetHeight )
{
	UIImage* uiImage;
	uiImage = (UIImage*)uiImagePtr;
	
	if(!uiImage) return false;
	
	CGContextRef spriteContext;
	CGImageRef	cgImage = uiImage.CGImage;
	
	int bytesPerPixel	= CGImageGetBitsPerPixel(cgImage)/8;
	if(bytesPerPixel == 3) bytesPerPixel = 4;
	
	int width			= targetWidth > 0 ? targetWidth : CGImageGetWidth(cgImage);
	int height			= targetHeight > 0 ? targetHeight : CGImageGetHeight(cgImage);
	
	// Allocated memory needed for the bitmap context
	GLubyte *pixels		= (GLubyte *) malloc(width * height * bytesPerPixel);
	
	// Uses the bitmatp creation function provided by the Core Graphics framework. 
	spriteContext = CGBitmapContextCreate(pixels, width, height, CGImageGetBitsPerComponent(cgImage), width * bytesPerPixel, CGImageGetColorSpace(cgImage), bytesPerPixel == 4 ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNone);
	
	if(spriteContext == NULL) {
		ofLog(OF_LOG_ERROR, "iPhoneUIImageToOFImage - CGBitmapContextCreate returned NULL");
		free(pixels);
		return false;
	}
	
	// After you create the context, you can draw the sprite image to the context.
	ofLog(OF_LOG_VERBOSE, "about to CGContextDrawImage");
	CGContextDrawImage(spriteContext, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height), cgImage);
	
	// You don't need the context at this point, so you need to release it to avoid memory leaks.
	ofLog(OF_LOG_VERBOSE, "about to CGContextRelease");
	CGContextRelease(spriteContext);
	
	int glMode;
	
	switch(bytesPerPixel) {
		case 1:
			glMode = GL_LUMINANCE;
			break;
		case 3: 
			glMode = GL_RGB;
			break;
		case 4: 
		default:
			glMode = GL_RGBA; break;
	}
	
	outTexture.allocate(width, height, glMode);
	outTexture.loadData(pixels, width, height, glMode);
	
	free(pixels);
	
	return true;
}

#endif