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
	
	virtual void setup	() {};
	virtual void update	() {};
	virtual void draw	() {};
	
	void setFill			( bool value );
	void setFillColor		( int value );
	void setFillAlpha		( float value );
	
	void setStroke			( bool value );
	void setStrokeColor		( int value );
	void setStrokeAlpha		( int value );
	void setStrokeWeight	( int value );
	
	void setRectangle		( float x, float y, float width, float height );
	void setOval			( float x, float y, float width, float height );
	void setCustom			( const vector<ofPoint>& points );
	
protected:
	
	virtual void updateOnFrame	();
	virtual void drawOnFrame	();
	
private:
	
	int				shapeType;
	
	float			shape_x;
	float			shape_y;
	float			shape_width;
	float			shape_height;
	
	bool			bShapeFill;
	int				shapeFillColor;
	float			shapeFillAlpha;
	int				shapeFillColorR;
	int				shapeFillColorG;
	int				shapeFillColorB;
	int				shapeFillColorA;
	
	bool			bShapeStroke;
	int				shapeStrokeColor;
	float			shapeStrokeAlpha;
	int				shapeStrokeColorR;
	int				shapeStrokeColorG;
	int				shapeStrokeColorB;
	int				shapeStrokeColorA;
	int				shapeStrokeWeight;
	
	vector<ofPoint>	shapePoints;
	
	void drawRectangle			();
	void drawRectangleFill		();
	void drawRectangleStroke	();
	
	void drawOval		();
	void drawOvalFill	();
	void drawOvalStroke	();
	
	void drawCustom		();
};