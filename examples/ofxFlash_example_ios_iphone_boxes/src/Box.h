/*
 *  Icon.h
 *  emptyExample
 *
 *  Created by Lukasz Karluk on 16/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxFlash.h"

class Box : public ofxFlashSprite
{

public:
	
	Box()
	{
		rotInc = ofRandom( -0.5, 0.5 );
		
		int sw = ofGetScreenWidth();
		int sh = ofGetScreenHeight();
		
		float w = ofRandom( sw * 0.1, sw * 0.2 );
		float h = ofRandom( sh * 0.1, sh * 0.2 );
		
		// have to set the display object rectangle for any mouse interaction to work.
		// this will be done via setting x, y, width, height properties of the sprite in the future.
		// but for now, it may look ugly but it works!
		
		_rect.set_to_rect( -w * 0.5, -h * 0.5, w * 0.5, h * 0.5 );
	}
	
	~Box()
	{
		//
	}
	
	float rotInc;
	
	void update ()
	{
		float r = rotation();
		rotation( r + rotInc );
	}
	
	void draw ()
	{
		float x = _rect.get_x_min();		// same as top left x.
		float y = _rect.get_y_min();		// same as top left y.
		float w = _rect.width();
		float h = _rect.height();

		if( mouseDown() )
		{
			ofFill();
			ofSetColor( 0, 255, 255 );
			ofRect( x, y, w, h );
		}
		else if( mouseOver() )
		{
			ofFill();
			ofSetColor( 255, 0, 255 );
			ofRect( x, y, w, h );
		}
		else
		{
			ofFill();
			ofSetColor( 150, 150, 150 );
			ofRect( x, y, w, h );
		}
		
		ofNoFill();
		ofSetLineWidth( 1 );
		ofSetColor( 100, 100, 100 );
		ofRect( x, y, w, h );
	}
	
};