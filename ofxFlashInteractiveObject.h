/*
 *  ofxFlashInteractiveObject.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 *	Ported from ofxMSAInteractiveObject.
 *	https://github.com/of/ofx-msa/tree/master/ofxMSAInteractiveObject/
 *
 */

#pragma once

#include "ofxFlashDisplayObject.h"

class ofxFlashInteractiveObject : public ofxFlashDisplayObject
{
	
public:
	
	 ofxFlashInteractiveObject();
	~ofxFlashInteractiveObject();

	const bool&		doubleClickEnabled ();
	void			doubleClickEnabled ( bool value );
	
	const bool&		mouseEnabled ();
	void			mouseEnabled ( bool value );
	
	const bool&		mouseOver	();
	const bool&		mouseDown	();
	
private:
	
	bool	_doubleClickEnabled;
	bool	_mouseEnabled;
	bool	_tabEnabled;
	int		_tabIndex;
	
	bool	_mouseOver;
	bool	_mouseDown;
	
	void	enableMouseEvents	();
	void	disableMouseEvents	();
	
	void	_mouseMoved		( ofMouseEventArgs &e );
	void	_mousePressed	( ofMouseEventArgs &e );
	void	_mouseDragged	( ofMouseEventArgs &e );
	void	_mouseReleased	( ofMouseEventArgs &e );
	
};