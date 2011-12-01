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
	typeID		= OFX_FLASH_TYPE_DISPLAY_OBJECT;

	_name				= "sprite";
	_libraryItemName	= "";
	
	_alpha			= 1.0;
	_compoundAlpha	= 1.0;
	_visible		= true;
	_width			= 0.0;
	_height			= 0.0;
	_x				= 0.0;
	_y				= 0.0;
	_z				= 0.0;
	_mouseX			= 0.0;
	_mouseY			= 0.0;
	_rotation		= 0.0;
	_rotationX		= 0.0;
	_rotationY		= 0.0;
	_rotationZ		= 0.0;
	_scaleX			= 1.0;
	_scaleY			= 1.0;
	_scaleZ			= 1.0;
	_blendMode		= BLEND_MODE_NORMAL;
	_level			= -1;
	
	mask		= NULL;
	parent		= NULL;
	stage		= NULL;
}

ofxFlashDisplayObject :: ~ofxFlashDisplayObject ()
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
	ofVertex( _rectTransformed[ 0 ].x, _rectTransformed[ 0 ].y );
	ofVertex( _rectTransformed[ 1 ].x, _rectTransformed[ 1 ].y );
	ofVertex( _rectTransformed[ 2 ].x, _rectTransformed[ 2 ].y );
	ofVertex( _rectTransformed[ 3 ].x, _rectTransformed[ 3 ].y );
	ofVertex( _rectTransformed[ 0 ].x, _rectTransformed[ 0 ].y );
	ofEndShape( true );
}

void ofxFlashDisplayObject :: drawPixelBounds ()
{
	if( _pixelBounds.is_null() )
		return;
	
	ofNoFill();
	ofSetColor( 255, 0, 0 );
	ofSetLineWidth( 2 );
	ofRect( _pixelBounds.get_x_min(), _pixelBounds.get_y_min(), _pixelBounds.width(), _pixelBounds.height() );
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

const float& ofxFlashDisplayObject :: compoundAlpha ()
{
	return _compoundAlpha;
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

//void
//DisplayObject::setWidth(double newwidth)
//{
//	const SWFRect& bounds = getBounds();
//	const double oldwidth = bounds.width();
//	assert(oldwidth >= 0); 
//	
//    const double xscale = oldwidth ? (newwidth / oldwidth) : 0; 
//    const double rotation = _rotation * PI / 180.0;
//	
//    SWFMatrix m = getMatrix();
//    const double yscale = m.get_y_scale(); 
//    m.set_scale_rotation(xscale, yscale, rotation);
//    setMatrix(m, true); 
//}

void ofxFlashDisplayObject :: width ( float value )
{
	_width = value;
    _rect.expand_to( _rect.get_x_min() + _width, 0 );
}

//============================================================= HEIGHT.

const float& ofxFlashDisplayObject :: height ()
{
	return _height;
}

//void
//DisplayObject::setHeight(double newheight)
//{
//	const SWFRect& bounds = getBounds();
//	
//	const double oldheight = bounds.height();
//	assert(oldheight >= 0); 
//	
//    const double yscale = oldheight ? (newheight / oldheight) : 0;
//    const double rotation = _rotation * PI / 180.0;
//	
//    SWFMatrix m = getMatrix();
//    const double xscale = m.get_x_scale();
//    m.set_scale_rotation(xscale, yscale, rotation);
//    setMatrix(m, true);
//}

void ofxFlashDisplayObject :: height ( float value )
{
	_height = value;
    _rect.expand_to( 0, _rect.get_y_min() + _height );
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
	if( stage )		// if it has a reference to stage then it must have been added as a child to stage.
	{
		ofPoint p;
		p.x = stage->mouseX();
		
		_concatenatedMatrixInv.transform( p );
		
		_mouseX = p.x - _rect.get_x_min();
	}
	else
	{
		_mouseX = 0;
	}
	
	return _mouseX;
}

const int& ofxFlashDisplayObject :: mouseY ()
{
	if( stage )		// if it has a reference to stage then it must have been added as a child to stage.
	{
		ofPoint p;
		p.y = stage->mouseY();
		
		_concatenatedMatrixInv.transform( p );
		
		_mouseY = p.y - _rect.get_y_min();
	}
	else
	{
		_mouseY = 0;
	}
	
	return _mouseY;
}

//============================================================= ROTATION.

const float& ofxFlashDisplayObject :: rotation ()
{
	return _rotation = _matrix.get_rotation() * RAD_TO_DEG;
}

void ofxFlashDisplayObject :: rotation ( float value )
{
	_matrix.set_rotation( _rotation = value * DEG_TO_RAD );
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

//============================================================= LEVEL.

const int& ofxFlashDisplayObject :: level ()
{
	return _level;
}

void ofxFlashDisplayObject :: level ( int value )
{
	_level = value;
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
	_rotation	= mat.get_rotation() * RAD_TO_DEG;
}

//============================================================= CONCATENATED MATRIX.

const ofxFlashMatrix& ofxFlashDisplayObject :: concatenatedMatrix ()
{
	return _concatenatedMatrix;
}

//============================================================= PIXEL BOUNDS.

const ofxFlashRectangle& ofxFlashDisplayObject :: pixelBounds ()
{
	return _pixelBounds;
}

void ofxFlashDisplayObject :: resetPixelBounds ()
{
	_pixelBounds.set_null();
}

void ofxFlashDisplayObject :: addToPixelBounds( const ofxFlashRectangle& rect )
{
	_pixelBounds.expand_to_rect( rect );
}

///////////////////////////////////////////////
//	TRANSFORM.
///////////////////////////////////////////////

void ofxFlashDisplayObject :: transform ( const ofxFlashMatrix& mat )
{
	_concatenatedMatrix		= mat;
	_concatenatedMatrixInv	= mat;
	_concatenatedMatrixInv.invert();
	
	float x1 = _rect.get_x_min();
	float y1 = _rect.get_y_min();
	float x2 = _rect.get_x_max();
	float y2 = _rect.get_y_max();
	
	ofPoint p0( x1, y1 );
	ofPoint p1( x2, y1 );
	ofPoint p2( x2, y2 );
	ofPoint p3( x1, y2 );
	
	mat.transform( p0 );
	mat.transform( p1 );
	mat.transform( p2 );
	mat.transform( p3 );
	
	_rectTransformed[ 0 ] = p0;
	_rectTransformed[ 1 ] = p1;
	_rectTransformed[ 2 ] = p2;
	_rectTransformed[ 3 ] = p3;
	
	//-- work out global bounding box.
	
	vector<ofPoint> points;
	points.push_back( _rectTransformed[ 0 ] );
	points.push_back( _rectTransformed[ 1 ] );
	points.push_back( _rectTransformed[ 2 ] );
	points.push_back( _rectTransformed[ 3 ] );
	
	_pixelBounds.set_null();						// reset before enclosing new points.
	_pixelBounds.enclose_rect( points );
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
	ofPoint p = point;
	
	_concatenatedMatrixInv.transform( p );

	return p;
}

ofPoint ofxFlashDisplayObject :: globalToLocal3D ( const ofPoint& point )
{
	ofPoint p = point;						// ofxFlashMatrix is a 3D matrix although only using the 2D component atm.
											// once the 3D maths is worked out, this should work.
	_concatenatedMatrixInv.transform( p );
	
	return p;
}

bool ofxFlashDisplayObject :: hitTestObject ( ofxFlashDisplayObject* obj )
{
	// TODO - working if two rectangles of different world matrices make any contact.
	
	return false;
}

bool ofxFlashDisplayObject :: hitTestPoint ( float x, float y, bool shapeFlag )
{
	ofPoint p( x, y );
	
	_concatenatedMatrixInv.transform( p );
	
	return _rect.point_test( p.x, p.y );
}

ofPoint ofxFlashDisplayObject :: local3DToGlobal ( const ofPoint& point )
{
	ofPoint p = point;						// ofxFlashMatrix is a 3D matrix although only using the 2D component atm.
											// once the 3D maths is worked out, this should work.
	_concatenatedMatrix.transform( p );
	
	return p;
}

ofPoint ofxFlashDisplayObject :: localToGlobal ( const ofPoint& point )
{
	ofPoint p = point;
	
	_concatenatedMatrix.transform( p );
	
	return p;
}