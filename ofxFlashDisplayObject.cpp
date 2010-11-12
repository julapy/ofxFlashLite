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

	_name				= "sprite";
	_libraryItemName	= "";
	
	_alpha		= 1.0;
	_visible	= true;
	_width		= 0.0;
	_height		= 0.0;
	_x			= 0.0;
	_y			= 0.0;
	_z			= 0.0;
	_mouseX		= 0.0;
	_mouseY		= 0.0;
	_rotation	= 0.0;
	_rotationX	= 0.0;
	_rotationY	= 0.0;
	_rotationZ	= 0.0;
	_scaleX		= 1.0;
	_scaleY		= 1.0;
	_scaleZ		= 1.0;
	_blendMode	= BLEND_MODE_NORMAL;
	
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

void ofxFlashDisplayObject :: drawTransformedOutline ()
{
	ofNoFill();
	ofSetColor( 0, 255, 0 );
	ofSetLineWidth( 2 );
	
	ofBeginShape();
	ofVertex( rectTransformed[ 0 ].x, rectTransformed[ 0 ].y );
	ofVertex( rectTransformed[ 1 ].x, rectTransformed[ 1 ].y );
	ofVertex( rectTransformed[ 2 ].x, rectTransformed[ 2 ].y );
	ofVertex( rectTransformed[ 3 ].x, rectTransformed[ 3 ].y );
	ofVertex( rectTransformed[ 0 ].x, rectTransformed[ 0 ].y );
	ofEndShape( true );
}

void ofxFlashDisplayObject :: drawBoundingBox ()
{
	ofNoFill();
	ofSetColor( 255, 0, 0 );
	ofSetLineWidth( 2 );
	ofRect( rectGlobal.get_x_min(), rectGlobal.get_y_min(), rectGlobal.width(), rectGlobal.height() );
}

///////////////////////////////////////////////
//	GETTER / SETTERS.
///////////////////////////////////////////////

//============================================================= NAME.

const string& ofxFlashDisplayObject :: name ()
{
	return _name;
}

void ofxFlashDisplayObject :: name ( string value )
{
	_name = value;
}

//============================================================= LIBRARY ITEM NAME.

const string& ofxFlashDisplayObject :: libraryItemName ()
{
	return _libraryItemName;
}

void ofxFlashDisplayObject :: libraryItemName ( string value )
{
	_libraryItemName = value;
}

//============================================================= ALPHA.

const float& ofxFlashDisplayObject :: alpha ()
{
	return _alpha;
}

void ofxFlashDisplayObject :: alpha ( float value )
{
	_alpha = value;
}

//============================================================= VISIBLE.

const bool& ofxFlashDisplayObject :: visible ()
{
	return _visible;
}

void ofxFlashDisplayObject :: visible ( bool value )
{
	_visible = value;
}

//============================================================= WIDTH.

const float& ofxFlashDisplayObject :: width ()
{
	return _width;
}

void ofxFlashDisplayObject :: width ( float value )
{
	_width = value;
}

//============================================================= HEIGHT.

const float& ofxFlashDisplayObject :: height ()
{
	return _height;
}

void ofxFlashDisplayObject :: height ( float value )
{
	_height = value;
}

//============================================================= X.

const float& ofxFlashDisplayObject :: x ()
{
	return _x = _matrix.getTx();
}

void ofxFlashDisplayObject :: x ( float value )
{
	_matrix.setTx( _x = value );
}

//============================================================= Y.

const float& ofxFlashDisplayObject :: y ()
{
	return _y = _matrix.getTy();
}

void ofxFlashDisplayObject :: y ( float value )
{
	_matrix.setTy( _y = value );
}

//============================================================= Z.

const float& ofxFlashDisplayObject :: z ()
{
	return _z;
}

void ofxFlashDisplayObject :: z ( float value )
{
	_z = value;
}

//============================================================= MOUSE X / Y.

const int& ofxFlashDisplayObject :: mouseX ()
{
	return _mouseX;
}

const int& ofxFlashDisplayObject :: mouseY ()
{
	return _mouseY;
}

//============================================================= ROTATION.

const float& ofxFlashDisplayObject :: rotation ()
{
	return _rotation = _matrix.get_rotation();
}

void ofxFlashDisplayObject :: rotation ( float value )
{
	_matrix.set_rotation( _rotation = value );
}

//============================================================= ROTATION X.

const float& ofxFlashDisplayObject :: rotationX ()
{
	return _rotationX;
}

void ofxFlashDisplayObject :: rotationX ( float value )
{
	_rotationX = value;
}

//============================================================= ROTATION Y.

const float& ofxFlashDisplayObject :: rotationY ()
{
	return _rotationY;
}

void ofxFlashDisplayObject :: rotationY ( float value )
{
	_rotationY = value;
}

//============================================================= ROTATION Z.

const float& ofxFlashDisplayObject :: rotationZ ()
{
	return _rotationZ;
}

void ofxFlashDisplayObject :: rotationZ ( float value )
{
	_rotationZ = value;
}

//============================================================= SCALE X.

const float& ofxFlashDisplayObject :: scaleX ()
{
	return _scaleX = _matrix.get_x_scale();
}

void ofxFlashDisplayObject :: scaleX ( float value )
{
	_matrix.set_x_scale( _scaleX = value );
}

//============================================================= SCALE Y.

const float& ofxFlashDisplayObject :: scaleY ()
{
	return _scaleY = _matrix.get_y_scale();
}

void ofxFlashDisplayObject :: scaleY ( float value )
{
	_matrix.set_y_scale( _scaleY = value );
}

//============================================================= SCALE Z.

const float& ofxFlashDisplayObject :: scaleZ ()
{
	return _scaleZ;
}

void ofxFlashDisplayObject :: scaleZ ( float value )
{
	_scaleZ = value;
}

//============================================================= BLEND MODE.

const int& ofxFlashDisplayObject :: blendMode ()
{
	return _blendMode;
}

void ofxFlashDisplayObject :: blendMode ( int value )
{
	if( value < 0 || value > 13 )		// invalid range.
		return;
	
	_blendMode = value;
}

//============================================================= MATRIX.

const ofxFlashMatrix& ofxFlashDisplayObject :: matrix()
{
	return _matrix;
}

void ofxFlashDisplayObject :: matrix( const ofxFlashMatrix& mat )
{
	_matrix = mat;
	
	_x			= mat.getTx();
	_y			= mat.getTy();
	_scaleX		= mat.get_x_scale();
	_scaleY		= mat.get_y_scale();
	_rotation	= mat.get_rotation();
}

///////////////////////////////////////////////
//	TRANSFORM.
///////////////////////////////////////////////

void ofxFlashDisplayObject :: transform ( const ofxFlashMatrix& mat )
{
	float x1 = rectLocal.get_x_min();
	float y1 = rectLocal.get_y_min();
	float x2 = rectLocal.get_x_max();
	float y2 = rectLocal.get_y_max();
	
	ofPoint p0( x1, y1 );
	ofPoint p1( x2, y1 );
	ofPoint p2( x2, y2 );
	ofPoint p3( x1, y2 );
	
	mat.transform( p0 );
	mat.transform( p1 );
	mat.transform( p2 );
	mat.transform( p3 );
	
	rectTransformed[ 0 ] = p0;
	rectTransformed[ 1 ] = p1;
	rectTransformed[ 2 ] = p2;
	rectTransformed[ 3 ] = p3;
	
	//-- work out global bounding box.
	
	vector<ofPoint> points;
	points.push_back( rectTransformed[ 0 ] );
	points.push_back( rectTransformed[ 1 ] );
	points.push_back( rectTransformed[ 2 ] );
	points.push_back( rectTransformed[ 3 ] );
	
	rectGlobal.enclose_rect( points );
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