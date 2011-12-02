/*
 *  ofxFlashInteractiveObject.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashInteractiveObject.h"


ofxFlashInteractiveObject :: ofxFlashInteractiveObject()
{
	typeID = OFX_FLASH_TYPE_INTERACTIVE_OBJECT;
	
	_doubleClickEnabled	= false;
	_mouseEnabled		= false;
	_mouseUpOutside		= true;
	
	_tabEnabled			= false;
	_tabIndex			= 0;
	
	_mouseOver			= false;
	_mouseDown			= false;
	
	mouseOverDirty		= false;
	mouseDownDirty		= false;
}

ofxFlashInteractiveObject :: ~ofxFlashInteractiveObject ()
{
//	if( _mouseEnabled )
//	{
//		disableMouseEvents();
//	}
}

//============================================================= DOUBLE CLICK ENABLED.

const bool& ofxFlashInteractiveObject :: doubleClickEnabled ()
{
	return _doubleClickEnabled;
}

void ofxFlashInteractiveObject :: doubleClickEnabled ( bool value )
{
	_doubleClickEnabled = value;
}

//============================================================= MOUSE ENABLED.

const bool& ofxFlashInteractiveObject :: mouseEnabled ()
{
	return _mouseEnabled;
}

void ofxFlashInteractiveObject :: mouseEnabled ( bool value )
{
	if( _mouseEnabled == value )
		return;
	
	_mouseEnabled = value;
	
//	if( _mouseEnabled )
//	{
//		enableMouseEvents();
//	}
//	else
//	{
//		disableMouseEvents();
//	}
}

//============================================================= MOUSE UP OUTSIDE.

const bool& ofxFlashInteractiveObject :: mouseUpOutside ()
{
	return _mouseUpOutside;
}

void ofxFlashInteractiveObject :: mouseUpOutside ( bool value )
{
	_mouseUpOutside = value;
}

//============================================================= MOUSE OVER.

void ofxFlashInteractiveObject :: mouseOver ( bool value )
{
	_mouseOver = value;
}

const bool&	ofxFlashInteractiveObject :: mouseOver ()
{
	return _mouseOver;
}

//============================================================= MOUSE DOWN.

void ofxFlashInteractiveObject :: mouseDown ( bool value )
{
	_mouseDown = value;
}

const bool& ofxFlashInteractiveObject :: mouseDown ()
{
	return _mouseDown;
}

//============================================================= ENABLE / DISABLE MOUSE.

void ofxFlashInteractiveObject :: enableMouseEvents()
{
#ifdef OF_USING_POCO
	ofAddListener( ofEvents.mouseMoved,		this, &ofxFlashInteractiveObject :: _mouseMoved		);
	ofAddListener( ofEvents.mouseDragged,	this, &ofxFlashInteractiveObject :: _mouseDragged	);
	ofAddListener( ofEvents.mousePressed,	this, &ofxFlashInteractiveObject :: _mousePressed	);
	ofAddListener( ofEvents.mouseReleased,	this, &ofxFlashInteractiveObject :: _mouseReleased	);
#endif
}

void ofxFlashInteractiveObject :: disableMouseEvents()
{
#ifdef OF_USING_POCO
	ofRemoveListener( ofEvents.mouseMoved,		this, &ofxFlashInteractiveObject :: _mouseMoved		);
	ofRemoveListener( ofEvents.mouseDragged,	this, &ofxFlashInteractiveObject :: _mouseDragged	);
	ofRemoveListener( ofEvents.mousePressed,	this, &ofxFlashInteractiveObject :: _mousePressed	);
	ofRemoveListener( ofEvents.mouseReleased,	this, &ofxFlashInteractiveObject :: _mouseReleased	);
#endif
}

//============================================================= MOUSE EVENT HANDLERS.

void ofxFlashInteractiveObject :: _mouseMoved( int x, int y, int id )
{
	if( !_mouseEnabled )
		return;
	
	// dispatch mouse move - should dispatch first.
	
	if( hitTestPoint( x, y ) )
	{
		if( !_mouseOver )
		{
			_mouseOver = true;
			
			// dispatch mouse over
		}
	}
	else if( _mouseOver )
	{
		_mouseOver = false;
		
		// dispatch mouse out.
		
		if( _mouseUpOutside && _mouseDown )
		{
			_mouseDown = false;
			
			// dispatch mouse up.
		}
	}
}

void ofxFlashInteractiveObject :: _mouseDragged( int x, int y, int id )
{
	if( !_mouseEnabled )
		return;
	
	// dispatch mouse drag - should dispatch first.
	
	if( hitTestPoint( x, y ) )
	{
		if( !_mouseOver )
		{
			_mouseOver = true;
			
			// dispatch mouse over
		}
	}
	else
	{
		if( _mouseOver )
		{
			_mouseOver = false;
			
			// dispatch mouse out.
			
			if( _mouseUpOutside && _mouseDown )
			{
				_mouseDown = false;
				
				// dispatch mouse up.
			}
		}
	}
}

void ofxFlashInteractiveObject :: _mousePressed( int x, int y, int id )
{
	if( !_mouseEnabled )
		return;
	
	if( hitTestPoint( x, y ) )
	{
		if( !_mouseDown )
		{
			_mouseDown = true;
			
			// dispatch mouse down.
		}
	}
}

void ofxFlashInteractiveObject :: _mouseReleased( int x, int y, int id )
{
	if( !_mouseEnabled )
		return;
	
	if( hitTestPoint( x, y ) )
	{
		// dispatch mouse up inside.
	}
	else
	{
		if( _mouseDown )
		{
			// dispatch mouse up outside.
		}
	}
	
	_mouseDown = false;
}

