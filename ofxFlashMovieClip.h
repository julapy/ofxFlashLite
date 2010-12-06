/*
 *  ofxFlashMovieClip.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofxFlashSprite.h"

class ofxFlashMovieClip : public ofxFlashSprite
{

public:
	
	 ofxFlashMovieClip();
	~ofxFlashMovieClip();
	
	//======================================= INTERNAL METHODS - these methods are to be used by ofxFlash only.
	
	void setTotalFrames	( int totalFrames = 1 );
	ofxFlashDisplayObject* addChildToFrame( ofxFlashDisplayObject* child, int frameNum );
	
	virtual void updateInternal	();
	
	//======================================= GENERIC OVERRIDE METHODS.
	
	virtual void setup	();
	virtual void update	();
	virtual void draw	();
	
	//======================================= AS3 METHODS.
	
	void gotoAndPlay	( int frameNum );
	void gotoAndStop	( int frameNum );
	void nextFrame		();
	void prevFrame		();
	void play			();
	void stop			();
	
	int totalFrames		();
	int currentFrame	();
	
private:
	
	void addFrameChildren		();
	void removeFrameChildren	();
	
	vector<ofxFlashDisplayObjectContainer*>	frames;
	ofxFlashDisplayObjectContainer*			frame;
	
	int		frameIndex;
	bool	bPlay;
	
};