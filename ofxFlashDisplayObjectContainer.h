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
	
	bool		mouseChildren;
	int			numChildren;
	bool		tabChildren;
	
	vector<ofxFlashDisplayObject*>	children;
	
	ofxFlashDisplayObject*			addChild				( ofxFlashDisplayObject* child );
	ofxFlashDisplayObject*			addChildAt				( ofxFlashDisplayObject* child, int index );
	bool							contains				( ofxFlashDisplayObject* child );
	ofxFlashDisplayObject*			getChildAt				( int index );
	ofxFlashDisplayObject*			getChildByName			( string name );
	int								getChildIndex			( ofxFlashDisplayObject* child );
	vector<ofxFlashDisplayObject*>	getObjectsUnderPoint	( ofPoint point );
	ofxFlashDisplayObject*			removeChild				( ofxFlashDisplayObject* child );
	ofxFlashDisplayObject*			removeChildAt			( int index );
	void							setChildIndex			( ofxFlashDisplayObject* child, int index );
	void							swapChildren			( ofxFlashDisplayObject* child1, ofxFlashDisplayObject* child2 );
	void							swapChildrenAt			( int index1, int index2 );
	
};