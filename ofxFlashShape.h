/*
 *  ofxFlashShape.h
 *  emptyExample
 *
 *  Created by Lukasz Karluk on 9/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashDisplayObject.h"

#define UNDEFINED_SHAPE_TYPE	0
#define RECTANGLE_SHAPE_TYPE	1
#define OVAL_SHAPE_TYPE			2
#define CUSTOM_SHAPE_TYPE		3

class ofxFlashShape : public ofxFlashDisplayObject
{

public:
	
	 ofxFlashShape();
	~ofxFlashShape();
	
	virtual void setup	();
	virtual void update	();
	virtual void draw	();
	
	void setFill			( bool value );
	void setStroke			( bool value );
	void setFillColor		( int value );
	void setStrokeColor		( int value );
	void setStrokeWeight	( int value );
	
	void setRectangle		( float x, float y, float width, float height );
	void setOval			( float x, float y, float width, float height );
	void setCustom			( const vector<ofPoint>& points );
	
private:
	
	int				shapeType;
	float			shape_x;
	float			shape_y;
	float			shape_width;
	float			shape_height;
	vector<ofPoint>	shapePoints;
	bool			bShapeFill;
	bool			bShapeStroke;
	int				shapeFillColor;
	int				shapeStrokeColor;
	int				shapeStrokeWeight;
	
	void drawRectangle	();
	void drawOval		();
	void drawCustom		();
	
};