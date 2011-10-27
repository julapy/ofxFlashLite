/*
 *  ofxFlashFXL.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 3/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashXFL.h"

ofxFlashXFL :: ofxFlashXFL()
{
	bLoaded     = false;
    bVerbose    = false;
}

ofxFlashXFL :: ~ofxFlashXFL()
{
	//
}

///////////////////////////////////////////
//	
///////////////////////////////////////////


vector<DOMBitmapItem>	domBitmapItems;


///////////////////////////////////////////
//	LOAD XFL.
///////////////////////////////////////////

bool ofxFlashXFL :: loadFile ( const string& file )
{
	vector<string> xflFileSplit;
	xflFileSplit	= ofSplitString( file, "/" );
	
	xflFile			= xflFileSplit[ xflFileSplit.size() - 1 ];
	xflFolder		= "";
	for( int i=0; i<xflFileSplit.size()-1; i++ )	// drop the file
	{
		xflFolder += xflFileSplit[ i ] + "/";
	}
	
	string xflPath;
	xflPath = xflFolder + xflFile;
	
    if( bVerbose )
    {
        cout << "Loading, " << xflPath << endl;
    }
	
	bLoaded = xml.loadFile( xflPath );
	
	if( !bLoaded )
	{
        if( bVerbose )
        {
            cout << "DOMDocument.xml did not load." << endl;
        }
		
		return bLoaded;
	}
	
	loadXFLMedia();
	loadAssets();
	
	return bLoaded;
}

void ofxFlashXFL :: loadXFLMedia ()
{
	xml.pushTag( "DOMDocument", 0 );
	
	if( !xml.tagExists( "media", 0 ) )
		return;
	
	xml.pushTag( "media", 0 );
	
	int numOfMediaTags;
	numOfMediaTags = xml.getNumTags( "DOMBitmapItem" );
	
	for( int i=0; i<numOfMediaTags; i++ )
	{
		DOMBitmapItem item;
		item.name						= xml.getAttribute( "DOMBitmapItem", "name",					"", i );
		item.itemID						= xml.getAttribute( "DOMBitmapItem", "itemID",					"", i );
		item.sourceExternalFilepath		= xml.getAttribute( "DOMBitmapItem", "sourceExternalFilepath",	"", i );
		item.sourceLastImported			= xml.getAttribute( "DOMBitmapItem", "sourceLastImported",		0,  i );
		item.sourcePlatform				= xml.getAttribute( "DOMBitmapItem", "sourcePlatform",			"", i );
		item.externalFileSize			= xml.getAttribute( "DOMBitmapItem", "externalFileSize",		0,  i );
		item.originalCompressionType	= xml.getAttribute( "DOMBitmapItem", "originalCompressionType",	"", i );
		item.quality					= xml.getAttribute( "DOMBitmapItem", "quality",					0,  i );
		item.href						= xml.getAttribute( "DOMBitmapItem", "href",					"", i );
		item.bitmapDataHRef				= xml.getAttribute( "DOMBitmapItem", "bitmapDataHRef",			"", i );
		item.frameRight					= xml.getAttribute( "DOMBitmapItem", "frameRight",				0,  i );
		item.frameBottom				= xml.getAttribute( "DOMBitmapItem", "frameBottom",				0,  i );
		
		domBitmapItems.push_back( item );
	}
	
	xml.popTag();
}

///////////////////////////////////////////
//	LOAD ASSETS.
///////////////////////////////////////////

void ofxFlashXFL :: loadAssets ()
{
	ofxFlashLibrary* library;
	library = ofxFlashLibrary :: getInstance();
	
	for( int i=0; i<domBitmapItems.size(); i++ )
	{
		const DOMBitmapItem& item = domBitmapItems[ i ];
		int mediaType	= determineMediaType( item.sourceExternalFilepath );
		string path		= xflFolder + item.sourceExternalFilepath;
		
        bool success = false;
		
		if( mediaType == OFX_FLASH_LIBRARY_TYPE_IMAGE )
		{
			success = library->addImage( item.name, path );
		}
		else if( mediaType == OFX_FLASH_LIBRARY_TYPE_VIDEO )
		{
			success = library->addVideo( item.name, path );
		}
		else if( mediaType == OFX_FLASH_LIBRARY_TYPE_SOUND )
		{
			success = library->addSound( item.name, path );
		}
        
        if( bVerbose )
        {
            if( success )
            {
                cout << "asset loaded :: " << path << endl;
            }
            else
            {
                cout << "asset failed :: " << path << endl;
            }
        }
	}
}

int ofxFlashXFL :: determineMediaType ( string fileName )
{
	return OFX_FLASH_LIBRARY_TYPE_IMAGE;					// TODO :: work out correct file type.
}

///////////////////////////////////////////
//	BUILD.
///////////////////////////////////////////

void ofxFlashXFL :: build ()
{
	if( !bLoaded )
		return;
	
	ofxFlashStage* stage;
	stage = ofxFlashStage :: getInstance();
	
	ofxFlashXFLBuilder* builder;
	builder = new ofxFlashXFLBuilder();
	builder->build( xflFolder + xflFile, stage->root() );
	
	stage->update();
}