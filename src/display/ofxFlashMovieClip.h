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

/** 
 *  Forward Declarations to prevent Cyclic Dependency.
 *  http://www.eventhelix.com/RealtimeMantra/HeaderFileIncludePatterns.htm
**/
class ofxFlashXFLBuilder;
class ofxFlashLibrary;


class ofxFlashMovieClip : public ofxFlashSprite
{

public:
	
	 ofxFlashMovieClip();
	~ofxFlashMovieClip();
    
    friend class ofxFlashXFLBuilder;    // friends! http://www.cplusplus.com/doc/tutorial/inheritance/
    friend class ofxFlashLibrary;
	
	virtual void setup	() {};
	virtual void update	() {};
	virtual void draw	() {};
    
    //----------------------------------------- movie clip methods.
	void gotoAndPlay	( int frameNum );
	void gotoAndStop	( int frameNum );
	void nextFrame		();
	void prevFrame		();
	void play			();
	void stop			();
	
	int totalFrames		();
	int currentFrame	();
    
    //------------------------------------------------------------------- display object container override.
    ofxFlashDisplayObject* addChild ( ofxFlashDisplayObject* child ) {
        return frame->addChild( child );
    }
    
    ofxFlashDisplayObject* addChildAt ( ofxFlashDisplayObject* child, int index ) {
        return frame->addChildAt( child, index );
    }
    
    bool contains ( ofxFlashDisplayObject* child ) {
        return frame->contains( child );
    }
    
    ofxFlashDisplayObject* getChildAt ( int index ) {
        return frame->getChildAt( index );
    }
    
    ofxFlashDisplayObject* getChildByName ( string name ) {
        return frame->getChildByName( name );
    }
    
    int	getChildIndex ( ofxFlashDisplayObject* child ) {
        return frame->getChildIndex( child );
    }
    
    vector<ofxFlashDisplayObject*> getObjectsUnderPoint ( ofPoint point ) {
        return frame->getObjectsUnderPoint( point );
    }
    
    ofxFlashDisplayObject* removeChild ( ofxFlashDisplayObject* child ) {
        return frame->removeChild( child );
    }
    
    ofxFlashDisplayObject* removeChildAt ( int index ) {
        return frame->removeChildAt( index );
    }
    
    void setChildIndex ( ofxFlashDisplayObject* child, int index ) {
        frame->setChildIndex( child, index );
    }
    
    void swapChildren ( ofxFlashDisplayObject* child1, ofxFlashDisplayObject* child2 ) {
        frame->swapChildren( child1, child2 );
    }
    
    void swapChildrenAt	( int index1, int index2 ) {
        frame->swapChildrenAt( index1, index2 );
    }
	
protected:
	
	virtual void updateOnFrame	();
	
private:
    
	void setTotalFrames	( int totalFrames = 1 );
	
	void addFrameChildren		();
	void removeFrameChildren	();
	
	vector<ofxFlashDisplayObjectContainer*>	frames;
	ofxFlashDisplayObjectContainer*			frame;
	
	int		frameIndex;
	bool	bPlay;
	
};