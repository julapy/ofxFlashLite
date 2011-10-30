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
//	LOAD XFL.
///////////////////////////////////////////

bool ofxFlashXFL :: loadFile ( const string& file )
{
	vector<string> xflFileSplit;
	xflFileSplit	= ofSplitString( file, "/" );
	
	xflFile	= xflFileSplit[ xflFileSplit.size() - 1 ];
	xflRoot = "";
	for( int i=0; i<xflFileSplit.size()-1; i++ )	// drop the file
		xflRoot += xflFileSplit[ i ] + "/";
	
	string xflPath;
	xflPath = xflRoot + xflFile;
	
	bLoaded = xml.loadFile( xflPath );

    if( bVerbose )
    {
        if( bLoaded )
            cout << "[ ofxFlashXFL :: loadFile ] - loading XFL - SUCCESS :: " << xflPath << endl;
        else
            cout << "[ ofxFlashXFL :: loadFile ] - loading XFL - FAILED  :: " << xflPath << endl;
    }
    
	if( !bLoaded )
		return bLoaded;
    
    xml.pushTag( "DOMDocument", 0 );
    {
        loadXFLMedia();
        loadXFLSymbols();
        loadAssets();
    }
    xml.popTag();
	
	return bLoaded;
}

void ofxFlashXFL :: loadXFLMedia ()
{
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

void ofxFlashXFL :: loadXFLSymbols ()
{
	if( !xml.tagExists( "symbols", 0 ) )
		return;
    
    ofxFlashLibrary* library;
    library = ofxFlashLibrary :: getInstance();
	
	xml.pushTag( "symbols", 0 );
	
	int numOfTags;
	numOfTags = xml.getNumTags( "Include" );
	
	for( int i=0; i<numOfTags; i++ )
	{
        ofxFlashLibrarySymbol *symbol;
        symbol = new ofxFlashLibrarySymbol();
		symbol->href            = xml.getAttribute( "Include", "href", "", i );
        symbol->loadImmediate   = xml.getAttribute( "Include", "loadImmediate",	"true", i ) == "true" ? true : false;
        symbol->xflRoot         = xflRoot;
        
        if( symbol->loadImmediate )
        {
            ofxXmlSettings xml;
            xml.loadFile( xflRoot + "LIBRARY/" + symbol->href );
            symbol->linkageClassName = xml.getAttribute( "DOMSymbolItem", "linkageClassName", "" );
        }
        
        library->addSymbol( symbol );
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
		string path		= xflRoot + "LIBRARY/" + item.href;
		
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
                cout << "[ ofxFlashXFL :: loadAssets ] - loading asset - SUCCESS :: " << path << endl;
            }
            else
            {
                cout << "[ ofxFlashXFL :: loadAssets ] - loading asset - FAILED  :: " << path << endl;
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
    builder->setVerbose( bVerbose );
	builder->build( xflRoot, xflFile, stage->root() );
	
	stage->update();
}
