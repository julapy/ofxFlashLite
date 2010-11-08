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
#include "ofxFlash.h"

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
	ofBaseImage*	imageAsset;
	ofSoundPlayer*	soundAsset;
	
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
	
public:
	
	static ofxFlashLibrary* getInstance()
	{
		if( !_instance )
		{
			_instance = new ofxFlashLibrary();
		}
		
        return _instance;
	}
	
	void addAsset	( string assetID, string assetPath, int assetType );
	void addImage	( string assetID, string assetPath );	
	void addImage	( string assetID, ofBaseImage& image );
	void addVideo	( string assetID, string assetPath );
	void addVideo	( string assetID, ofBaseImage& video );
	void addSound	( string assetID, string assetPath );
	void addSound	( string assetID, ofSoundPlayer& sound );
	
	ofSoundPlayer* getSound				( string assetID );
	ofSoundPlayer* getSoundByFileName	( string fileName );
	ofBaseImage* getAsset				( string assetID );
	ofBaseImage* getAssetByFileName		( string fileName );
	
	ofxFlashDisplayObject*	addDisplayObject	( string libraryItemName, ofxFlashDisplayObject* displayObject );
	ofxFlashDisplayObject*	getDisplayObject	( string libraryItemName );
	bool					hasDisplayObject	( string libraryItemName );
	
};