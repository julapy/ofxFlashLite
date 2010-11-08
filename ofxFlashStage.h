/*
 *  ofxStage.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashDisplayObjectContainer.h"

class ofxFlashStage : public ofxFlashDisplayObjectContainer
{
	
public:
	
	static ofxFlashStage* getInstance()
	{
		if( !_instance )
		{
			_instance = new ofxFlashStage();
		}
		
        return _instance;
	};
	
	void addListeners		();
	void removeListeners	();
	
	virtual void setup	();
	virtual void update	();
	virtual void draw	();
	
	///////////////////////////////////////////////
	//
	//	PRIVATE.
	//
	///////////////////////////////////////////////
	
private: 
	
	static ofxFlashStage* _instance;
	
	 ofxFlashStage();
	~ofxFlashStage();
	
	void update	( ofEventArgs &e );
	void draw	( ofEventArgs &e );
	
	void updateChildren	( vector<ofxFlashDisplayObject*>& children );
	void drawChildren	( vector<ofxFlashDisplayObject*>& children );
	
};