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
	_tabEnabled			= false;
	_tabIndex			= 0;
	
	_mouseOver			= false;
	_mouseDown			= false;
}

ofxFlashInteractiveObject :: ~ofxFlashInteractiveObject ()
{
	//
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
	ofAddListener( ofEvents.mousePressed,	this, &ofxFlashInteractiveObject :: _mousePressed	);
	ofAddListener( ofEvents.mouseMoved,		this, &ofxFlashInteractiveObject :: _mouseMoved		);
	ofAddListener( ofEvents.mouseDragged,	this, &ofxFlashInteractiveObject :: _mouseDragged	);
	ofAddListener( ofEvents.mouseReleased,	this, &ofxFlashInteractiveObject :: _mouseReleased	);
}

void ofxFlashInteractiveObject :: disableMouseEvents()
{
	ofRemoveListener( ofEvents.mousePressed,	this, &ofxFlashInteractiveObject :: _mousePressed	);
	ofRemoveListener( ofEvents.mouseMoved,		this, &ofxFlashInteractiveObject :: _mouseMoved		);
	ofRemoveListener( ofEvents.mouseDragged,	this, &ofxFlashInteractiveObject :: _mouseDragged	);
	ofRemoveListener( ofEvents.mouseReleased,	this, &ofxFlashInteractiveObject :: _mouseReleased	);
}

//============================================================= MOUSE EVENT HANDLERS.

void ofxFlashInteractiveObject :: _mouseMoved( ofMouseEventArgs &e )
{
	if( !_mouseEnabled )
		return;
	
//	_mouseX = x;
//	_mouseY = y;
	
	if( hitTestPoint( e.x, e.y ) )
	{
		if(!_mouseOver)
		{
			// dispatch roll over event.
			
			_mouseOver = true;
		}
		
		// dispatch mouse move event.
	}
	else if( _mouseOver )
	{
		// dispatch roll out event.
		
		_mouseOver = false;
	}
}


void ofxFlashInteractiveObject :: _mousePressed( ofMouseEventArgs &e )
{
	if( !_mouseEnabled )
		return;
	
//	_mouseX = x;
//	_mouseY = y;
	
	if( hitTestPoint( e.x, e.y ) )
	{
		if( !_mouseDown )
		{
			// dispatch mouse down event.
			
			_mouseDown = true;
		}
	}
}

void ofxFlashInteractiveObject :: _mouseDragged( ofMouseEventArgs &e )
{
	if( !_mouseEnabled )
		return;
	
//	_mouseX = x;
//	_mouseY = y;
	
	if( hitTestPoint( e.x, e.y ) )
	{
		if( !_mouseOver )
		{
			_mouseOver = true;
		}
		
		// dispatch mouse dragg event.
	}
	else
	{
		if( _mouseOver )
		{
			// dispatch mouse out event.
			
			_mouseOver = false;
		}
		
		if( _mouseDown )
		{
			// dispatch drag outside event.
		}
	}
}

void ofxFlashInteractiveObject :: _mouseReleased( ofMouseEventArgs &e )
{
	if( !_mouseEnabled )
		return;
	
//	_mouseX = x;
//	_mouseY = y;
	
	if( hitTestPoint( e.x, e.y ) )
	{
		// dispatch on release inside event.
	}
	else
	{
		if( _mouseDown )
		{
			// dispatch on release outside event.
		}
	}
	
	_mouseDown = false;
}

