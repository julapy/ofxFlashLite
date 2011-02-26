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
	void setTouchMode		( bool value );
	
	const int&	mouseX	();
	const int&	mouseY	();
	
	virtual void setup	();
	virtual void update	();
	virtual void draw	();
	
	void mouseMoved		( int x, int y, int id );
	void mouseDragged	( int x, int y, int id );
	void mousePressed	( int x, int y, int id );
	void mouseReleased	( int x, int y, int id );
	
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
	bool bTouchMode;
	
	bool bMouseDown;
	bool bMousePressed;
	bool bMouseReleased;
	bool bMouseChanged;
	int  mouseID;
	
	ofxFlashDisplayObject*	topMostHitDisplayObject;
	ofxFlashDisplayObject*	topMostHitDisplayObjectPrev;
	
	vector<ofxFlashInteractiveObject*> lineTopDown;
	vector<ofxFlashInteractiveObject*> lineTopDownPrev;
	vector<ofxFlashInteractiveObject*> lineBottomUp;
	vector<ofxFlashInteractiveObject*> lineBottomUpPrev;
	
	int	_stageMouseX;
	int	_stageMouseY;
	
	//---------------------------------------------

#ifdef OF_USING_POCO	
	void update	( ofEventArgs &e );
	void draw	( ofEventArgs &e );
#endif
	
	void updateChildrenOne	( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	void updateChildrenTwo	( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	void updateMouse		();
	
	void drawChildren		( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	void drawChildrenDebug	( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children );
	
	bool canHaveChildren		( ofxFlashDisplayObject* displayObject );
	bool isInteractiveObject	( ofxFlashDisplayObject* displayObject );
	
#ifdef OF_USING_POCO	
	void mouseMoved		( ofMouseEventArgs& e )	{ mouseMoved	( e.x, e.y, 0 ); };
	void mouseDragged	( ofMouseEventArgs& e )	{ mouseDragged	( e.x, e.y, 0 ); };
	void mousePressed	( ofMouseEventArgs& e )	{ mousePressed	( e.x, e.y, 0 ); };
	void mouseReleased	( ofMouseEventArgs& e )	{ mouseReleased	( e.x, e.y, 0 ); };
#endif
};