/*
 *  ofxFlashShape.cpp
 *  emptyExample
 *
 *  Created by Lukasz Karluk on 9/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashShape.h"

ofxFlashShape :: ofxFlashShape()
{
    typeID = OFX_FLASH_TYPE_SHAPE;
    
	shapeType = UNDEFINED_SHAPE_TYPE;
	
	setFill( false );
	setStroke( false );
	
	setFillColor( 0x000000 );
	setFillAlpha( 1.0 );
	
	setStrokeColor( 0x000000 );
	setStrokeAlpha( 1.0 );
	setStrokeWeight( 0 );
}

ofxFlashShape :: ~ofxFlashShape()
{
	//
}

///////////////////////////////////////////////
//	RUNTIME METHODS.
///////////////////////////////////////////////

void ofxFlashShape :: updateOnFrame ()
{
	//
}

void ofxFlashShape :: drawOnFrame ()
{
	if( shapeType == UNDEFINED_SHAPE_TYPE )
	{
		return;
	}
	else if( shapeType == RECTANGLE_SHAPE_TYPE )
	{
		drawRectangle();
	}
	else if( shapeType == OVAL_SHAPE_TYPE )
	{
		drawOval();
	}
	else if( shapeType == CUSTOM_SHAPE_TYPE )
	{
		drawCustom();
	}
}

///////////////////////////////////////////////
//	SHAPE CONFIG.
///////////////////////////////////////////////

void ofxFlashShape :: setFill( bool value )
{
	bShapeFill = value;
}

void ofxFlashShape :: setFillColor ( int value )
{
	shapeFillColor	= value;
	shapeFillColorR	= ( value >> 16 ) & 0xFF;
	shapeFillColorG = ( value >> 8 ) & 0xFF;
	shapeFillColorB	= value & 0xFF;	
}

void ofxFlashShape :: setFillAlpha ( float value )
{
	shapeFillAlpha	= value;
	shapeFillColorA	= value * 255;
	
	if( value == 0 )
		bShapeFill = false;
}

void ofxFlashShape :: setStroke ( bool value )
{
	bShapeStroke = value;
}

void ofxFlashShape :: setStrokeColor ( int value )
{
	shapeStrokeColor	= value;
	shapeStrokeColorR	= ( value >> 16 ) & 0xFF;
	shapeStrokeColorG	= ( value >> 8 ) & 0xFF;
	shapeStrokeColorB	= value & 0xFF;	
}

void ofxFlashShape :: setStrokeAlpha ( int value )
{
	shapeStrokeAlpha	= value;
	shapeStrokeColorA	= value * 255;
	
	if( value == 0 )
		bShapeStroke = false;
}

void ofxFlashShape :: setStrokeWeight ( int value )
{
	shapeStrokeWeight = value;
}

void ofxFlashShape :: setRectangle ( float x, float y, float width, float height )
{
	shapeType = RECTANGLE_SHAPE_TYPE;
	
	shape_x			= x;
	shape_y			= y;
	shape_width		= width;
	shape_height	= height;
	
	this->width( shape_width );
	this->height( shape_height );
	
	_rect.set_to_rect( x, y, x + width, y + height );
}

void ofxFlashShape :: setOval ( float x, float y, float width, float height )
{
	shapeType = OVAL_SHAPE_TYPE;
	
	shape_x			= x;
	shape_y			= y;
	shape_width		= width;
	shape_height	= height;

	this->width( shape_width );
	this->height( shape_height );
	
	_rect.set_to_rect( x, y, x + width, y + height );
}

void ofxFlashShape :: setCustom ( const vector<ofPoint>& points )
{
	shapeType = CUSTOM_SHAPE_TYPE;
	
	// TODO :: work out x, y, width, height (bounding rectangle) from points.
}

///////////////////////////////////////////////
//	DRAW RECTANGLE.
///////////////////////////////////////////////

void ofxFlashShape :: drawRectangle ()
{
	drawRectangleFill();
	drawRectangleStroke();
}

void ofxFlashShape :: drawRectangleFill ()
{
	if( !bShapeFill )
		return;
	
	float a = parent->compoundAlpha() * shapeFillAlpha;
	
	ofFill();
	ofSetColor( shapeFillColorR, shapeFillColorG, shapeFillColorB, a * 255 );
	
	ofRect
	(
		shape_x,
		shape_y,
		shape_width,
		shape_height
	);
}

void ofxFlashShape :: drawRectangleStroke ()
{
	if( !bShapeStroke )
		return;
	
	float a = parent->compoundAlpha() * shapeStrokeAlpha;
	
	ofNoFill();
	ofSetLineWidth( shapeStrokeWeight );
	ofSetColor( shapeStrokeColorR, shapeStrokeColorG, shapeStrokeColorB, a * 255 );
	
	ofRect
	(
		shape_x,
		shape_y,
		shape_width,
		shape_height
	);
}

///////////////////////////////////////////////
//	DRAW OVAL.
///////////////////////////////////////////////

void ofxFlashShape :: drawOval ()
{
	drawOvalFill();
	drawOvalStroke();
}

void ofxFlashShape :: drawOvalFill ()
{
	if( !bShapeFill )
		return;
	
	float a = parent->compoundAlpha() * shapeFillAlpha;
	
	ofFill();
	ofSetColor( shapeFillColorR, shapeFillColorG, shapeFillColorB, a * 255 );
	
	ofEllipse
	(
		shape_x + shape_width  * 0.5,
		shape_y + shape_height * 0.5,
		shape_width,
		shape_height
	);
}

void ofxFlashShape :: drawOvalStroke ()
{
	if( !bShapeStroke )
		return;
	
	float a = parent->compoundAlpha() * shapeStrokeAlpha;
	
	ofNoFill();
	ofSetLineWidth( shapeStrokeWeight );
	ofSetColor( shapeStrokeColorR, shapeStrokeColorG, shapeStrokeColorB, a * 255 );
	
	ofEllipse
	(
		shape_x + shape_width  * 0.5,
		shape_y + shape_height * 0.5,
		shape_width,
		shape_height
	);
}

///////////////////////////////////////////////
//	DRAW CUSTOM.
///////////////////////////////////////////////

void ofxFlashShape :: drawCustom ()
{
	// TODO
}

