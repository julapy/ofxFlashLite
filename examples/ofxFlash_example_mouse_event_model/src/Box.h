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
	
	Box( int w, int h )
	{
		rotInc = 0;
		
		boxW = w;
		boxH = h;
		
		// have to set the display object rectangle for any mouse interaction to work.
		// this will be done via setting x, y, width, height properties of the sprite in the future.
		// but for now, it may look ugly but it works!
		
		_rect.set_to_rect( -w * 0.5, -h * 0.5, w * 0.5, h * 0.5 );
		
		font.loadFont( "Arial", 7 );
	}
	
	~Box()
	{
		//
	}
	
	float rotInc;
	int boxW;
	int boxH;
	ofTrueTypeFont font;
	
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
		ofSetColor( 50, 50, 50 );
		ofRect( x, y, w, h );
		
		ofSetColor( 0x000000 );
		
		string text;
		text  = "mouseEnabled :: ";
		text += mouseEnabled() ? "true" : "false";
		font.drawString( text, -55, -6 );
		
		text = "mouseChildren :: ";
		text += mouseChildren() ? "true" : "false";
		font.drawString( text, -55, 7 );
	}
	
};