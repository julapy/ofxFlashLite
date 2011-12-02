/*
 *  ofxFlashFXL.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 3/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxFlashLibrary.h"
#include "ofxFlashStage.h"
#include "ofxFlashMovieClip.h"
#include "ofxFlashXFLBuilder.h"
#include "ofxXmlSettings.h"

struct DOMBitmapItem
{
	string	name;
	string	itemID;
	string	sourceExternalFilepath;
	int		sourceLastImported;
	string	sourcePlatform;
	int		externalFileSize;
	string	originalCompressionType;
	int		quality;
	string	href;
	string	bitmapDataHRef;
	int		frameRight;
	int		frameBottom;
};

class ofxFlashXFL
{

public:
	
	 ofxFlashXFL();
	~ofxFlashXFL();
	
	ofxXmlSettings	xml;
    string			xflRoot;
	string			xflFile;
	bool			bLoaded;
    bool            bVerbose;
    
    void setVerbose         ( bool value ) { bVerbose = value; }
	
	bool loadFile			( const string& xflFile );
	void build				();
	
private:

	void loadXFLMedia		();
    void loadXFLSymbols     ();
    void loadAssets			();
	int  determineMediaType	( string fileName );
    
    vector<DOMBitmapItem> domBitmapItems;
};