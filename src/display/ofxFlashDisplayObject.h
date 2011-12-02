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
#include "ofxFlashTransform.h"

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
	
	friend class ofxFlashStage;			// friends! http://www.cplusplus.com/doc/tutorial/inheritance/
	
	virtual void setup	() {};
	virtual void update	() {};
	virtual void draw	() {};
	
	void drawTransformedOutline	();
	void drawPixelBounds		();
	
	///////////////////////////////////////////////
	//
	//	DISPLAY OBJECT.
	//	http://livedocs.adobe.com/flex/3/langref/flash/display/DisplayObject.html
	//
	///////////////////////////////////////////////

	const string&			name ();
	void					name ( string value );

	const string&			libraryItemName ();
	void					libraryItemName ( string value );
	
	const float&			alpha ();
	void					alpha ( float value );
	
	const float&			compoundAlpha ();

	const bool&				visible ();
	void					visible ( bool value );

	const float&			width ();
	void					width ( float value );

	const float&			height ();
	void					height ( float value );

	const float&			x ();
	void					x ( float value );

	const float&			y ();
	void					y ( float value );
	
	const float&			z ();
	void					z ( float value );
	
	virtual const int&		mouseX ();				// is overwritten by stage.
	virtual const int&		mouseY ();				// is overwritten by stage.

	const float&			rotation ();
	void					rotation ( float value );

	const float&			rotationX ();
	void					rotationX ( float value );

	const float&			rotationY ();
	void					rotationY ( float value );

	const float&			rotationZ ();
	void					rotationZ ( float value );

	const float&			scaleX ();
	void					scaleX ( float value );

	const float&			scaleY ();
	void					scaleY ( float value );

	const float&			scaleZ ();
	void					scaleZ ( float value );

	const int&				blendMode ();
	void					blendMode ( int value );

	const int&				level ();
	void					level ( int value );
	
	const ofxFlashMatrix&		matrix				();
	void						matrix				( const ofxFlashMatrix& mat );
	
	const ofxFlashMatrix&		concatenatedMatrix	();
	
	const ofxFlashRectangle&	pixelBounds			();
	
	//=============================================================

	ofxFlashDisplayObject*	mask;			// DisplayObject in AS3.
	ofxFlashDisplayObject*	parent;			// DisplayObjectContainer in AS3.
	ofxFlashDisplayObject*	stage;			// Stage in AS3.
	
	//=============================================================
	
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
	
protected:
	
	virtual void updateOnFrame	() {};		// updateOnFrame is called on every update loop by stage. any updates should go in there.
	virtual void drawOnFrame	() {};		// drawOnFrame is called on every draw loop by stage.
	
	ofxFlashMatrix		_matrix;
	ofxFlashMatrix		_concatenatedMatrix;
	ofxFlashMatrix		_concatenatedMatrixInv;
	ofxFlashRectangle	_rect;
	ofPoint				_rectTransformed[ 4 ];
	ofxFlashRectangle	_pixelBounds;
    
    ofxFlashTransform   _transform;
	
private:
	
	void resetPixelBounds	();
	void addToPixelBounds	( const ofxFlashRectangle& rect );
	
	void transform			( const ofxFlashMatrix& mat );
	
	string		_name;
	string		_libraryItemName;
	
	float		_alpha;
	float		_compoundAlpha;
	bool		_visible;
	float		_width;
	float		_height;
	float		_x;
	float		_y;
	float		_z;
	int			_mouseX;
	int			_mouseY;
	float		_rotation;
	float		_rotationX;
	float		_rotationY;
	float		_rotationZ;
	float		_scaleX;
	float		_scaleY;
	float		_scaleZ;
	int			_blendMode;
	int			_level;
	
};