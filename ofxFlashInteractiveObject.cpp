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
	typeID = OFX_FLASH_INTERACTIVE_OBJECT_TYPE;
	
	_doubleClickEnabled	= false;
	_mouseEnabled		= false;
	_mouseUpOutside		= true;
	
	_tabEnabled			= false;
	_tabIndex			= 0;
	
	_mouseOver			= false;
	_mouseDown			= false;
}

ofxFlashInteractiveObject :: ~ofxFlashInteractiveObject ()
{
	if( _mouseEnabled )
	{
		disableMouseEvents();
	}
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
	
	if( _mouseEnabled )
	{
		enableMouseEvents();
	}
	else
	{
		disableMouseEvents();
	}
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

//============================================================= MOUSE STATE GETTERS.

const bool&	ofxFlashInteractiveObject :: mouseOver ()
{
	return _mouseOver;
}

const bool& ofxFlashInteractiveObject :: mouseDown ()
{
	return _mouseDown;
}

//============================================================= ENABLE / DISABLE MOUSE.

void ofxFlashInteractiveObject :: enableMouseEvents()
{
	ofAddListener( ofEvents.mouseMoved,		this, &ofxFlashInteractiveObject :: _mouseMoved		);
	ofAddListener( ofEvents.mouseDragged,	this, &ofxFlashInteractiveObject :: _mouseDragged	);
	ofAddListener( ofEvents.mousePressed,	this, &ofxFlashInteractiveObject :: _mousePressed	);
	ofAddListener( ofEvents.mouseReleased,	this, &ofxFlashInteractiveObject :: _mouseReleased	);
}

void ofxFlashInteractiveObject :: disableMouseEvents()
{
	ofRemoveListener( ofEvents.mouseMoved,		this, &ofxFlashInteractiveObject :: _mouseMoved		);
	ofRemoveListener( ofEvents.mouseDragged,	this, &ofxFlashInteractiveObject :: _mouseDragged	);
	ofRemoveListener( ofEvents.mousePressed,	this, &ofxFlashInteractiveObject :: _mousePressed	);
	ofRemoveListener( ofEvents.mouseReleased,	this, &ofxFlashInteractiveObject :: _mouseReleased	);
}

//============================================================= MOUSE EVENT HANDLERS.

void ofxFlashInteractiveObject :: _mouseMoved( ofMouseEventArgs &e )
{
	if( !_mouseEnabled )
		return;
	
	// dispatch mouse move - should dispatch first.
	
	if( hitTestPoint( e.x, e.y ) )
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

void ofxFlashInteractiveObject :: _mouseDragged( ofMouseEventArgs &e )
{
	if( !_mouseEnabled )
		return;
	
	// dispatch mouse drag - should dispatch first.
	
	if( hitTestPoint( e.x, e.y ) )
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

void ofxFlashInteractiveObject :: _mousePressed( ofMouseEventArgs &e )
{
	if( !_mouseEnabled )
		return;
	
	if( hitTestPoint( e.x, e.y ) )
	{
		if( !_mouseDown )
		{
			_mouseDown = true;
			
			// dispatch mouse down.
		}
	}
}

void ofxFlashInteractiveObject :: _mouseReleased( ofMouseEventArgs &e )
{
	if( !_mouseEnabled )
		return;
	
	if( hitTestPoint( e.x, e.y ) )
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

