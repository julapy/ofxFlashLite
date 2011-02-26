/*
 *  ofxFlashLibrary.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashLibrary.h"


ofxFlashLibrary* ofxFlashLibrary :: _instance = NULL;


ofBaseDraws* ofxFlashLibrary :: loadImage( string imagePath )
{
#ifdef TARGET_OF_IPHONE
	return ofxFlashLibraryLoaderIOS :: getInstance()->loadImage( imagePath );
#else
	return ofxFlashLibraryLoader :: getInstance()->loadImage( imagePath );
#endif
}

ofBaseDraws* ofxFlashLibrary :: loadVideo( string videoPath )
{
#ifdef TARGET_OF_IPHONE
	return ofxFlashLibraryLoaderIOS :: getInstance()->loadVideo( videoPath );
#else
	return ofxFlashLibraryLoader :: getInstance()->loadVideo( videoPath );
#endif
}

//================================================== GENERAL.

void ofxFlashLibrary :: addAsset( string assetID, string assetPath, int assetType )
{
	if( assetType == OFX_FLASH_LIBRARY_TYPE_IMAGE )
	{
		addImage( assetPath, assetID );
	}
	else if( assetType == OFX_FLASH_LIBRARY_TYPE_VIDEO )
	{
		addVideo( assetPath, assetID );
	}
	else if( assetType == OFX_FLASH_LIBRARY_TYPE_SOUND )
	{
		addSound( assetPath, assetID );
	}
}

//================================================== IMAGE.

void ofxFlashLibrary :: addImage ( string assetID, string assetPath )
{
	ofBaseDraws* tex = loadImage( assetPath );
	
	if( !tex )
		return;
	
	ofxFlashLibraryItem* item;
	item = new ofxFlashLibraryItem();
	item->assetID		= assetID;
	item->assetPath		= assetPath;
	item->assetType		= OFX_FLASH_LIBRARY_TYPE_IMAGE;
	item->imageAsset	= tex;
	item->soundAsset	= NULL;
	
	items.push_back( item );
	imageItems.push_back( item );
}

void ofxFlashLibrary :: addImage ( string assetID, ofBaseDraws& image )
{
	ofxFlashLibraryItem* item;
	item = new ofxFlashLibraryItem();
	item->assetID		= assetID;
	item->assetPath		= "";
	item->assetType		= OFX_FLASH_LIBRARY_TYPE_IMAGE;
	item->imageAsset	= &image;
	item->soundAsset	= NULL;
	
	items.push_back( item );
	imageItems.push_back( item );
}

//================================================== VIDEO.

void ofxFlashLibrary :: addVideo ( string assetID, string assetPath )
{
	ofBaseDraws* video = loadImage( assetPath );
	
	if( !video )
		return;
	
	ofxFlashLibraryItem* item;
	item = new ofxFlashLibraryItem();
	item->assetID		= assetID;
	item->assetPath		= assetPath;
	item->assetType		= OFX_FLASH_LIBRARY_TYPE_VIDEO;
	item->imageAsset	= video;
	item->soundAsset	= NULL;
	
	items.push_back( item );
	videoItems.push_back( item );
}

void ofxFlashLibrary :: addVideo ( string assetID, ofBaseDraws& video )
{
	ofxFlashLibraryItem* item;
	item = new ofxFlashLibraryItem();
	item->assetID		= assetID;
	item->assetPath		= "";
	item->assetType		= OFX_FLASH_LIBRARY_TYPE_VIDEO;
	item->imageAsset	= &video;
	item->soundAsset	= NULL;
	
	items.push_back( item );
	videoItems.push_back( item );
}

//================================================== SOUND.

void ofxFlashLibrary :: addSound ( string assetID, string assetPath )
{
	ofSoundPlayer* sound;
	sound = new ofSoundPlayer();
	sound->loadSound( assetPath, true );	// stream set to true - not sure what to do about this right now?
	
	ofxFlashLibraryItem* item;
	item = new ofxFlashLibraryItem();
	item->assetID		= assetID;
	item->assetPath		= assetPath;
	item->assetType		= OFX_FLASH_LIBRARY_TYPE_SOUND;
	item->imageAsset	= NULL;
	item->soundAsset	= sound;
	
	items.push_back( item );
	soundItems.push_back( item );
}

void ofxFlashLibrary :: addSound ( string assetID, ofSoundPlayer& sound )
{
	ofxFlashLibraryItem* item;
	item = new ofxFlashLibraryItem();
	item->assetID		= assetID;
	item->assetPath		= "";
	item->assetType		= OFX_FLASH_LIBRARY_TYPE_SOUND;
	item->imageAsset	= NULL;
	item->soundAsset	= &sound;
	
	items.push_back( item );
	soundItems.push_back( item );
}

ofSoundPlayer* ofxFlashLibrary :: getSound ( string assetID )
{
	for( int i=0; i<soundItems.size(); i++ )
	{
		ofxFlashLibraryItem& item = *soundItems[ i ];
		
		if( item.assetID == assetID )
		{
			return item.soundAsset;
		}
	}
	
	return NULL;
}

ofSoundPlayer* ofxFlashLibrary :: getSoundByFileName ( string fileName )
{
	if( fileName == "" )
		return NULL;
	
	for( int i=0; i<soundItems.size(); i++ )
	{
		ofxFlashLibraryItem& item = *soundItems[ i ];
		
		if( item.assetPath == fileName )
		{
			return item.soundAsset;
		}
	}
	
	return NULL;
}

//==================================================

ofBaseDraws* ofxFlashLibrary :: getAsset ( string assetID )
{
	for( int i=0; i<items.size(); i++ )
	{
		ofxFlashLibraryItem& item = *items[ i ];
		
		if( item.assetID == assetID )
		{
			return item.imageAsset;
		}
	}
	
	return NULL;
}

ofBaseDraws* ofxFlashLibrary :: getAssetByFileName ( string fileName )
{
	if( fileName == "" )
		return NULL;
	
	for( int i=0; i<items.size(); i++ )
	{
		ofxFlashLibraryItem& item = *items[ i ];
		
		if( item.assetPath == fileName )
		{
			return item.imageAsset;
		}
	}
	
	return NULL;
}

//================================================== DISPLAY OBJECTS.

ofxFlashDisplayObject* ofxFlashLibrary :: addDisplayObject ( string libraryItemName, ofxFlashDisplayObject* displayObject )
{
	if( !hasDisplayObject( displayObject->libraryItemName() ) )
	{
		displayObjects.push_back( displayObject );
	}
	
	return displayObject;
}

ofxFlashDisplayObject* ofxFlashLibrary :: getDisplayObject ( string libraryItemName )
{
	for( int i=0; i<displayObjects.size(); i++ )
	{
		ofxFlashDisplayObject* displayObject;
		displayObject = displayObjects[ i ];
		
		if( displayObject->libraryItemName() == libraryItemName )
		{
			return displayObject;
		}
	}
	
	return NULL;
}

bool ofxFlashLibrary :: hasDisplayObject ( string libraryItemName )
{
	for( int i=0; i<displayObjects.size(); i++ )
	{
		ofxFlashDisplayObject* displayObject;
		displayObject = displayObjects[ i ];
		
		if( displayObject->libraryItemName() == libraryItemName )
		{
			return true;
		}
	}
	
	return false;
}