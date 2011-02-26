/*
 *  ofxFlashRectangle.h
 *  emptyExample
 *
 *  Created by Lukasz Karluk on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 *	Original code ported from Gnash :: SWFRect
 *	http://www.gnu.org/software/gnash/
 *
 */



#pragma once

#include "ofMain.h"

class ofxFlashMatrix;		// forward decleration.

class ofxFlashRectangle
{

public:
	
	ofxFlashRectangle()
	{
		set_null();
	}
	
	~ofxFlashRectangle()
	{
		//
	}

	bool is_null() const
	{
		return ( _xMin == 0 && _xMax == 0 );
	}
	
	void set_null()
	{
		_xMin = _yMin = _xMax = _yMax = 0;
	}
	
	float width()
	{
		return _xMax - _xMin;
	}
	
	float height()
	{
		return _yMax - _yMin;
	}
	
	float get_x_min() const
	{
		return _xMin;
	}
	
	float get_x_max() const
	{
		return _xMax;
	}
	
	float get_y_min() const
	{
		return _yMin;
	}
	
	float get_y_max() const
	{
		return _yMax;
	}
    
	bool point_test( float x, float y )
	{
		if( is_null() )
			return false;
		
		if( x < _xMin || x > _xMax || y < _yMin || y > _yMax )
		{
			return false;
		} 
		
		return true;
    }
	
	void set_to_point( float x, float y )
	{
		_xMin = _xMax = x;
		_yMin = _yMax = y;
	}
	
	void set_to_rect( float x1, float y1, float x2, float y2 )
	{
		_xMin = x1;
		_yMin = y1;
		_xMax = x2;
		_yMax = y2;
	}
    
	void expand_to_point( float x, float y )
	{
		if( is_null() )
		{
			set_to_point( x, y );
		}
		else
		{
			expand_to( x, y );
		}
	}
	
	void expand_to_circle( float x, float y, float radius )
	{
		if( is_null() )
		{
			_xMin = x - radius;
			_yMin = y - radius;
			_xMax = x + radius;
			_yMax = y + radius;
		}
		else
		{
			_xMin = MIN( _xMin, x - radius );
			_yMin = MIN( _yMin, y - radius );
			_xMax = MAX( _xMax, x + radius );
			_yMax = MAX( _yMax, y + radius );
		}
	}
	
	void expand_to_rect( const ofxFlashRectangle& r ) 
	{    
		if( r.is_null() )
			return;
		
		if( is_null() )
		{
			*this = r;
		}
		else
		{
			_xMin = MIN( _xMin, r.get_x_min() );
			_yMin = MIN( _yMin, r.get_y_min() );
			_xMax = MAX( _xMax, r.get_x_max() );
			_yMax = MAX( _yMax, r.get_y_max() );
		}
	}   

	void enclose_rect( const vector<ofPoint>& points )
	{   
		for( int i=0; i<points.size(); i++ )
		{
			if( i == 0 )
			{
				set_to_point( points[ 0 ].x, points[ 0 ].y );
				
				continue;
			}

			expand_to( points[ i ].x, points[ i ].y );
		}
	}
	
    void expand_to( float x, float y )
    {
        _xMin = MIN( _xMin, x );
        _yMin = MIN( _yMin, y );
        _xMax = MAX( _xMax, x );
        _yMax = MAX( _yMax, y );
    }
	
private:
	
	float _xMin;
	float _yMin;
	float _xMax;
	float _yMax;
};