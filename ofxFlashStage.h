/*
 *  ofxStage.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashMovieClip.h"
#include "ofxFlashMatrix.h"

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

	ofxFlashMovieClip* root	();
	void showRedrawRegions	( bool value );
	
	const int&	mouseX	();
	const int&	mouseY	();
	
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
	
	//---------------------------------------------
	
	ofxFlashMovieClip*	_root;
	bool bShowRedrawRegions;
	
	int	_stageMouseX;
	int	_stageMouseY;
	
	//---------------------------------------------
	
	void update	( ofEventArgs &e );
	void draw	( ofEventArgs &e );
	
	void updateChildren		( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	void drawChildren		( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	void drawChildrenDebug	( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	
	void mouseMoved		( ofMouseEventArgs& e );
	void mouseDragged	( ofMouseEventArgs& e );
	
};