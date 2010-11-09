/*
 *  ofxFlashDisplayObject.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashDisplayObject.h"

ofxFlashDisplayObject :: ofxFlashDisplayObject ()
{
	typeID		= OFX_FLASH_DISPLAY_OBJECT_TYPE;

	name			= "sprite";
	libraryItemName = "";
	
	alpha		= 1.0;
	visible		= true;
	width		= 0.0;
	height		= 0.0;
	x			= 0.0;
	y			= 0.0;
	z			= 0.0;
	globalX		= 0.0;
	globalY		= 0.0;
	globalZ		= 0.0;
	mouseX		= 0.0;
	mouseY		= 0.0;
	rotation	= 0.0;
	rotationX	= 0.0;
	rotationY	= 0.0;
	rotationZ	= 0.0;
	scaleX		= 1.0;
	scaleY		= 1.0;
	scaleZ		= 1.0;
	blendMode	= BLEND_MODE_NORMAL;
	
	mat_a		= 1.0;
	mat_b		= 0.0;
	mat_c		= 0.0;
	mat_d		= 1.0;
	mat_tx		= 0.0;
	mat_ty		= 0.0;
	
	mask		= NULL;
	parent		= NULL;
	stage		= NULL;
}

ofxFlashDisplayObject :: ~ofxFlashDisplayObject ()
{
	//
}

///////////////////////////////////////////////
//	RUNTIME METHODS.
///////////////////////////////////////////////

void ofxFlashDisplayObject :: setup ()
{
	
}

void ofxFlashDisplayObject :: update ()
{
	//
}

void ofxFlashDisplayObject :: draw ()
{
	//
}

///////////////////////////////////////////////
//	BOUNDING BOX - DEBUG.
///////////////////////////////////////////////

void ofxFlashDisplayObject :: drawBoundingBox ()
{
	ofNoFill();
	ofSetColor( 255, 0, 0 );
	ofSetLineWidth( 1 );
	ofRect( globalX, globalY, width, height );
}

///////////////////////////////////////////////
//	DISPLAY OBJECT METHODS.
///////////////////////////////////////////////

ofRectangle ofxFlashDisplayObject :: getRect ( ofxFlashDisplayObject* targetCoordinateSpace )
{
	// TODO.
}

ofPoint ofxFlashDisplayObject :: globalToLocal ( const ofPoint& point )
{
	// TODO.
}

ofPoint ofxFlashDisplayObject :: globalToLocal3D ( const ofPoint& point )
{
	// TODO.
}

bool ofxFlashDisplayObject :: hitTestObject ( ofxFlashDisplayObject* obj )
{
	// TODO.
}

bool ofxFlashDisplayObject :: hitTestPoint ( float x, float y, bool shapeFlag )
{
	// TODO.
}

ofPoint ofxFlashDisplayObject :: local3DToGlobal ( const ofPoint& point )
{
	// TODO.
}

ofPoint ofxFlashDisplayObject :: localToGlobal ( const ofPoint& point )
{
	// TODO.
}