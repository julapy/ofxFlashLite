/*
 *  ofxFlashDisplayObject.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashEventDispatcher.h"

#define	BLEND_MODE_NORMAL		0
#define	BLEND_MODE_LAYER		1
#define	BLEND_MODE_MULTIPLY		2
#define	BLEND_MODE_SCREEN		3
#define	BLEND_MODE_LIGHTEN		4
#define	BLEND_MODE_DARKEN		5
#define	BLEND_MODE_DIFFERENCE	6
#define	BLEND_MODE_ADD			7
#define	BLEND_MODE_SUBTRACT		8
#define	BLEND_MODE_INVERT		9
#define	BLEND_MODE_ALPHA		10
#define	BLEND_MODE_ERASE		11
#define	BLEND_MODE_OVERLAY		12
#define	BLEND_MODE_HARDLIGHT	13



class ofxFlashStage;	// Forward Declarations to prevent Cyclic Dependency.
						// http://www.eventhelix.com/RealtimeMantra/HeaderFileIncludePatterns.htm


class ofxFlashDisplayObject : public ofxFlashEventDispatcher
{

public:
	
	 ofxFlashDisplayObject();
	~ofxFlashDisplayObject();
	
	virtual void setup	();
	virtual void update	();
	virtual void draw	();
	
	///////////////////////////////////////////////
	//
	//	DISPLAY OBJECT.
	//	http://livedocs.adobe.com/flex/3/langref/flash/display/DisplayObject.html
	//
	///////////////////////////////////////////////
	
	float		alpha;
	bool		visible;
	float		width;
	float		height;
	float		x;
	float		y;
	float		z;
	float		globalX;
	float		globalY;
	float		globalZ;
	int			mouseX;
	int			mouseY;
	float		rotation;
	float		rotationX;
	float		rotationY;
	float		rotationZ;
	float		scaleX;
	float		scaleY;
	float		scaleZ;
	int			blendMode;
	string		name;
	ofxFlashDisplayObject*	mask;			// DisplayObject in AS3.
	ofxFlashDisplayObject*	parent;			// DisplayObjectContainer in AS3.
	ofxFlashStage*			stage;			// Stage in AS3.
	
	string		libraryItemName;
	
	ofRectangle getRect			( ofxFlashDisplayObject* targetCoordinateSpace );
	ofPoint		globalToLocal	( const ofPoint& point );
	ofPoint		globalToLocal3D	( const ofPoint& point );
	bool		hitTestObject	( ofxFlashDisplayObject* obj );
	bool		hitTestPoint	( float x, float y, bool shapeFlag = false);
	ofPoint		local3DToGlobal	( const ofPoint& point );
	ofPoint		localToGlobal	( const ofPoint& point );
	
//	TODO :: cacheAsBitmap - maybe this can be an FBO?
//	TODO :: transform :: http://livedocs.adobe.com/flex/3/langref/flash/geom/Transform.html
//	TODO :: events - added, addedToStage, enterFrame, exitFrame, frameConstructed, removed, removedFromStage, render
	
};