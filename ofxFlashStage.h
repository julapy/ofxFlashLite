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
	bool bUsingListeners;
	bool bMouseDown;
	bool bMousePressed;
	bool bMouseReleased;
	
	ofxFlashDisplayObject*	topMostHitDisplayObject;
	ofxFlashDisplayObject*	topMostHitDisplayObjectPrev;
	
	vector<ofxFlashInteractiveObject*> lineTopDown;
	vector<ofxFlashInteractiveObject*> lineTopDownPrev;
	vector<ofxFlashInteractiveObject*> lineBottomUp;
	vector<ofxFlashInteractiveObject*> lineBottomUpPrev;
	
	int	_stageMouseX;
	int	_stageMouseY;
	
	//---------------------------------------------
	
	void update	( ofEventArgs &e );
	void draw	( ofEventArgs &e );
	
	void updateChildrenOne	( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	void updateChildrenTwo	( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	void updateMouse		();
	
	void drawChildren		( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	void drawChildrenDebug	( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	
	bool canHaveChildren		( ofxFlashDisplayObject* displayObject );
	bool isInteractiveObject	( ofxFlashDisplayObject* displayObject );
	
	void mouseMoved		( ofMouseEventArgs& e );
	void mouseDragged	( ofMouseEventArgs& e );
	void mousePressed	( ofMouseEventArgs& e );
	void mouseReleased	( ofMouseEventArgs& e );
};