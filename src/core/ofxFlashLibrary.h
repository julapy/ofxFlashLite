/*
 *  ofxFlashLibrary.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxFlashLibraryLoader.h"
#include "ofxFlashLibraryLoaderIOS.h"
#include "ofxFlashDisplayObject.h"
#include "ofxFlashMovieClip.h"
#include "ofxFlashXFLBuilder.h"

#define OFX_FLASH_LIBRARY_TYPE_IMAGE	0
#define OFX_FLASH_LIBRARY_TYPE_VIDEO	1
#define OFX_FLASH_LIBRARY_TYPE_SOUND	2

////////////////////////////////////////////////////////
//	OFX_FLASH_LIBRARY_ITEM
////////////////////////////////////////////////////////

class ofxFlashLibraryItem
{
	
public:
	
	string			assetID;
	string			assetPath;
	int				assetType;
	ofBaseDraws*	imageAsset;
	ofSoundPlayer*	soundAsset;
	
};

////////////////////////////////////////////////////////
//	OFX_FLASH_LIBRARY_SYMBOL
////////////////////////////////////////////////////////

class ofxFlashLibrarySymbol
{
public:
    string  href;               // property from DOMDocument.xml, symbols tag.
    bool    loadImmediate;      // property from DOMDocument.xml, symbols tag.

    string  xflRoot;            // added property for loading movieclip.
    string  linkageClassName;   // added property for loading movieclip.
};

////////////////////////////////////////////////////////
//	OFX_FLASH_LIBRARY
////////////////////////////////////////////////////////

class ofxFlashLibrary
{
	
private: 
	
	static ofxFlashLibrary* _instance;
	
	 ofxFlashLibrary() {};
	~ofxFlashLibrary() {};

	vector<ofxFlashLibraryItem*> items;
	vector<ofxFlashLibraryItem*> imageItems;
	vector<ofxFlashLibraryItem*> videoItems;
	vector<ofxFlashLibraryItem*> soundItems;
	vector<ofxFlashDisplayObject*> displayObjects;
    vector<ofxFlashLibrarySymbol*> symbols;
	
public:
	
	static ofxFlashLibrary* getInstance()
	{
		if( !_instance )
		{
			_instance = new ofxFlashLibrary();
		}
		
        return _instance;
	}
	
	bool addAsset	( string assetID, string assetPath, int assetType );
	bool addImage	( string assetID, string assetPath );	
	bool addImage	( string assetID, ofBaseDraws& image );
	bool addVideo	( string assetID, string assetPath );
	bool addVideo	( string assetID, ofBaseDraws& video );
	bool addSound	( string assetID, string assetPath );
	bool addSound	( string assetID, ofSoundPlayer& sound );
	
	ofBaseDraws* loadImage( string imagePath );
	ofBaseDraws* loadVideo( string videoPath );
	
	ofSoundPlayer* getSound				( string assetID );
	ofSoundPlayer* getSoundByFileName	( string fileName );
	ofBaseDraws* getAsset				( string assetID );
	ofBaseDraws* getAssetByFileName		( string fileName );
    
    void addSymbol ( ofxFlashLibrarySymbol *symbol );
    ofxFlashMovieClip* createMovieClipWithLinkageClassName ( string linkageClassName, ofxFlashMovieClip *container = NULL );
	
	ofxFlashDisplayObject*	addDisplayObject	( string libraryItemName, ofxFlashDisplayObject* displayObject );
	ofxFlashDisplayObject*	getDisplayObject	( string libraryItemName );
	bool					hasDisplayObject	( string libraryItemName );
};