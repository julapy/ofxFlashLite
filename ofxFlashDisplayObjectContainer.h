/*
 *  ofxFlashDisplayObjectContainer.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashInteractiveObject.h"

class ofxFlashDisplayObjectContainer : public ofxFlashInteractiveObject
{

public:
	
	 ofxFlashDisplayObjectContainer();
	~ofxFlashDisplayObjectContainer();
	
	const bool&			mouseChildren ();
	void				mouseChildren ( bool value );

	const bool&			tabChildren ();
	void				tabChildren ( bool value );
	
	int                 numChildren ();
	
	vector<ofxFlashDisplayObject*>	children;
	
	virtual ofxFlashDisplayObject*			addChild				( ofxFlashDisplayObject* child );
	virtual ofxFlashDisplayObject*			addChildAt				( ofxFlashDisplayObject* child, int index );
	virtual bool							contains				( ofxFlashDisplayObject* child );
	virtual ofxFlashDisplayObject*			getChildAt				( int index );
	virtual ofxFlashDisplayObject*			getChildByName			( string name );
	virtual int								getChildIndex			( ofxFlashDisplayObject* child );
	virtual vector<ofxFlashDisplayObject*>	getObjectsUnderPoint	( ofPoint point );
	virtual ofxFlashDisplayObject*			removeChild				( ofxFlashDisplayObject* child );
	virtual ofxFlashDisplayObject*			removeChildAt			( int index );
    virtual void                            removeAllChildren       ();
	virtual void							setChildIndex			( ofxFlashDisplayObject* child, int index );
	virtual void							swapChildren			( ofxFlashDisplayObject* child1, ofxFlashDisplayObject* child2 );
	virtual void							swapChildrenAt			( int index1, int index2 );
	
private:
	
	bool		_mouseChildren;
	bool		_tabChildren;
	int			_numChildren;
	
};