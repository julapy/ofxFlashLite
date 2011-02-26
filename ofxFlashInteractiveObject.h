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
	
	friend class ofxFlashStage;			// friends! http://www.cplusplus.com/doc/tutorial/inheritance/

	const bool&		doubleClickEnabled	();
	void			doubleClickEnabled	( bool value );
	
	const bool&		mouseEnabled		();
	void			mouseEnabled		( bool value );
	
	const bool&		mouseUpOutside		();
	void			mouseUpOutside		( bool value );
	
	const bool&		mouseOver			();
	const bool&		mouseDown			();
	
private:
	
	void			mouseOver			( bool value );	
	void			mouseDown			( bool value );
	
	bool	mouseOverDirty;
	bool	mouseDownDirty;
	
	bool	_doubleClickEnabled;
	bool	_mouseEnabled;
	bool	_mouseUpOutside;
	
	bool	_tabEnabled;
	int		_tabIndex;
	
	bool	_mouseOver;
	bool	_mouseDown;
	
	void	enableMouseEvents	();
	void	disableMouseEvents	();
	
#ifdef OF_USING_POCO
	void	_mouseMoved		( ofMouseEventArgs &e ) { _mouseMoved	 ( e.x, e.y, -1 ); };
	void	_mouseDragged	( ofMouseEventArgs &e ) { _mouseDragged	 ( e.x, e.y, -1 ); };
	void	_mousePressed	( ofMouseEventArgs &e ) { _mousePressed	 ( e.x, e.y, -1 ); };
	void	_mouseReleased	( ofMouseEventArgs &e ) { _mouseReleased ( e.x, e.y, -1 ); };
#endif
	
	void	_mouseMoved		( int x, int y, int id );
	void	_mouseDragged	( int x, int y, int id );
	void	_mousePressed	( int x, int y, int id );
	void	_mouseReleased	( int x, int y, int id );
};