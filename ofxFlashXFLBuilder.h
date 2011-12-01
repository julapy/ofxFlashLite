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
#include "ofxFlashShape.h"
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

struct DOMRectangleObject
{
	float	x;
	float	y;
	float	objectWidth;
	float	objectHeight;
};

struct DOMOvalObject
{
	float	x;
	float	y;
	float	objectWidth;
	float	objectHeight;
	float	endAngle;
};

//====================================================

class ofxFlashXFLBuilder : public ofxXmlSettings
{

public:
	
	 ofxFlashXFLBuilder();
	~ofxFlashXFLBuilder();
	
    void setVerbose( bool value ) { bVerbose = value; }
    
	void build ( const string& xflRoot, const string& xflFile, ofxFlashDisplayObjectContainer* container );
	
private:
	
    bool bVerbose;
    
	ofxFlashDisplayObjectContainer* container;
    string	xflRoot;
	string	xflFile;
	string	domType;
	int		totalFrames;
	
	DOMTimeline			domTimeline;
	DOMLayer			domLayer;
	DOMFrame			domFrame;
	DOMSymbolInstance	domSymbolInstance;
	DOMBitmapInstance	domBitmapInstance;
	DOMRectangleObject	domRectangleObject;
	DOMOvalObject		domOvalObject;
	
	void countTotalFrames		();
	void buildTimelines			();
	void buildLayers			();
	void buildFrames			();
	void buildElements			();
	void buildBitmap			();
	void buildMovieClip			();
	void buildRectangleShape	();
	void buildOvalShape			();
	
	void addDisplayObjectToFrames		( ofxFlashDisplayObject* displayObject );
	void setupMatrixForDisplayObject	( ofxFlashDisplayObject* displayObject );
	void setupColorForDisplayObject		( ofxFlashDisplayObject* displayObject );
	void setupFillForShape				( ofxFlashShape* shape );
	void setupStrokeForShape			( ofxFlashShape* shape );
	
	void pushTagAt			( int i );
	
	string cleanHexString	( string value );
	int  stringToHex		( string value );
	
};