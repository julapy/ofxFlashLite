/*
 *  ofxFlashXFLBuilder.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 5/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxFlashLibrary.h"
#include "ofxFlashMovieClip.h"
#include "ofxFlashBitmap.h"
#include "ofxXmlSettings.h"

#define DOM_DOCUMENT_TYPE		"DOMDocument"
#define DOM_SYMBOL_ITEM_TYPE	"DOMSymbolItem"

//====================================================

struct DOMTimeline
{
	string	name;
	int		currentFrame;
};

struct DOMLayer
{
	string	name;
	int		color;
	bool	locked;
	bool	current;
	bool	isSelected;
	bool	autoNamed;
	string	layerType;
};

struct DOMFrame
{
	int		index;
	int		duration;
	string	tweenType;
	bool	motionTweenSnap;
	int		keyMode;
};

struct DOMSymbolInstance
{
	string	libraryItemName;
	string	name;
	float	centerPoint3DX;
	float	centerPoint3DY;
};

struct DOMBitmapInstance
{
	string	libraryItemName;
	string	name;
	string	referenceID;
};

//====================================================

class ofxFlashXFLBuilder : public ofxXmlSettings
{

public:
	
	 ofxFlashXFLBuilder();
	~ofxFlashXFLBuilder();
	
	void build ( const string& xflFile, ofxFlashDisplayObjectContainer* container );
	
private:
	
	ofxFlashDisplayObjectContainer* container;
	string	xflFile;
	string	xflFolder;
	string	domType;
	int		totalFrames;
	
	DOMTimeline			domTimeline;
	DOMLayer			domLayer;
	DOMFrame			domFrame;
	DOMSymbolInstance	domSymbolInstance;
	DOMBitmapInstance	domBitmapInstance;
	
	void countTotalFrames	();
	void buildTimelines		();
	void buildLayers		();
	void buildFrames		();
	void buildElements		();
	void buildBitmap		();
	void buildMovieClip		();
	void setupDisplayObject ( ofxFlashDisplayObject* displayObject );
	
};