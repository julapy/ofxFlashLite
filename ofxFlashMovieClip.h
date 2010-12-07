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
	
	void setTotalFrames	( int totalFrames = 1 );
	ofxFlashDisplayObject* addChildToFrame( ofxFlashDisplayObject* child, int frameNum );
	
	virtual void setup	() {};
	virtual void update	() {};
	virtual void draw	() {};
	
	void gotoAndPlay	( int frameNum );
	void gotoAndStop	( int frameNum );
	void nextFrame		();
	void prevFrame		();
	void play			();
	void stop			();
	
	int totalFrames		();
	int currentFrame	();
	
protected:
	
	virtual void updateOnFrame	();
	
private:
	
	void addFrameChildren		();
	void removeFrameChildren	();
	
	vector<ofxFlashDisplayObjectContainer*>	frames;
	ofxFlashDisplayObjectContainer*			frame;
	
	int		frameIndex;
	bool	bPlay;
	
};