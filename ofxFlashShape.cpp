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
	shapeType = UNDEFINED_SHAPE_TYPE;
	
	setFill( false );
	setStroke( false );
	setFillColor( 0x000000 );
	setStrokeColor( 0x000000 );
	setStrokeWeight( 0 );
}

ofxFlashShape :: ~ofxFlashShape()
{
	//
}

///////////////////////////////////////////////
//	RUNTIME METHODS.
///////////////////////////////////////////////

void ofxFlashShape :: setup()
{
	
}

void ofxFlashShape :: update()
{
	
}

void ofxFlashShape :: draw()
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

void ofxFlashShape :: setStroke ( bool value )
{
	bShapeStroke = value;
}

void ofxFlashShape :: setFillColor ( int value )
{
	shapeFillColor = value;
}

void ofxFlashShape :: setStrokeColor ( int value )
{
	shapeStrokeColor = value;
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
	
	this->x			+= shape_x;
	this->y			+= shape_y;
	this->width		= shape_width;
	this->height	= shape_height;
}

void ofxFlashShape :: setOval ( float x, float y, float width, float height )
{
	shapeType = OVAL_SHAPE_TYPE;
	
	shape_x			= x + width  * 0.5;
	shape_y			= y + height * 0.5;
	shape_width		= width;
	shape_height	= height;

	this->x			+= shape_x;
	this->y			+= shape_y;
	this->width		= shape_width;
	this->height	= shape_height;
}

void ofxFlashShape :: setCustom ( const vector<ofPoint>& points )
{
	shapeType = CUSTOM_SHAPE_TYPE;
	
	// TODO :: work out x, y, width, height (bounding rectangle) from points.
}

///////////////////////////////////////////////
//	DRAW SHAPES.
///////////////////////////////////////////////

void ofxFlashShape :: drawRectangle ()
{
	if( bShapeFill )
	{
		ofFill();
		ofSetColor( shapeFillColor );
//		ofRect( shape_x, shape_y, shape_width, shape_height );
		ofRect( 0, 0, shape_width, shape_height );
	}
	
	if( bShapeStroke )
	{
		ofNoFill();
		ofSetLineWidth( shapeStrokeWeight );
		ofSetColor( shapeStrokeColor );
//		ofRect( shape_x, shape_y, shape_width, shape_height );
		ofRect( 0, 0, shape_width, shape_height );
	}
}

void ofxFlashShape :: drawOval ()
{
	if( bShapeFill )
	{
		ofFill();
		ofSetColor( shapeFillColor );
//		ofEllipse( shape_x, shape_y, shape_width, shape_height );
		ofEllipse( 0, 0, shape_width, shape_height );
	}
	
	if( bShapeStroke )
	{
		ofNoFill();
		ofSetLineWidth( shapeStrokeWeight );
		ofSetColor( shapeStrokeColor );
//		ofEllipse( shape_x, shape_y, shape_width, shape_height );
		ofEllipse( 0, 0, shape_width, shape_height );
	}
}

void ofxFlashShape :: drawCustom ()
{
	// TODO
}

