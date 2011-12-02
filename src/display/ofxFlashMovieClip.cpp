/*
 *  ofxFlashMovieClip.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashMovieClip.h"

ofxFlashMovieClip :: ofxFlashMovieClip( )
{
	typeID = OFX_FLASH_TYPE_MOVIECLIP;
	
	frame = new ofxFlashDisplayObjectContainer();		// create a single frame.
	frames.push_back( frame );							// add first frame to frames.
	frameIndex = 0;
	
	play();
}

ofxFlashMovieClip :: ~ofxFlashMovieClip()
{
	removeFrameChildren();
    
    for( int i=0; i<frames.size(); i++ )
        delete frames[ i ];
    
    frames.clear();
    frame = NULL;
}

///////////////////////////////////////////////
//	SETUP - INTERNAL.
///////////////////////////////////////////////

void ofxFlashMovieClip :: setTotalFrames ( int total )
{
	int t1	= total;
	int t2	= frames.size();
	int t	= MAX( t1, t2 );
	
	for( int i=0; i<t; i++ )
	{
		if( i > t2 - 1 )			// number of frames has increased, add more.
		{
			frames.push_back( new ofxFlashDisplayObjectContainer() );
		}
		else if( i > t1 - 1 )		// number of frames has decreased, remove some.
		{
			ofxFlashDisplayObjectContainer* frameToRemove;
			frameToRemove = frames[ i ];
			
			frames.erase( frames.begin() + i );
			
			--i;
			--t;
			
			delete frameToRemove;
			frameToRemove = NULL;
		}
	}
	
	frameIndex	= 0;
	this->frame	= frames[ frameIndex ];
}

///////////////////////////////////////////////
//	INTERNAL.
///////////////////////////////////////////////

void ofxFlashMovieClip :: updateOnFrame ()
{
	removeFrameChildren();			// remove + add is done on every frame. not the best idea, but will go with it for now.
	
	if( bPlay )
	{
		nextFrame();
	}
	
	addFrameChildren();
}

///////////////////////////////////////////////
//	FRAME CHILDREN.
///////////////////////////////////////////////

void ofxFlashMovieClip :: addFrameChildren ()
{
	for( int i=0; i<frame->children.size(); i++ )
	{
        ofxFlashDisplayObject *child;
        child = frame->children[ i ];
        
        // the child must be added manually, instead of using the addChild() method.
        // doing it this way ensures the child is not removed from the frames.
        // a movieclip can technically be added to only one parent, 
        // and as soon it is added to another it is removed from the previous parent.
        // with movieclip frames this is an exception and therefore movieclips have to be added like the below.

        children.push_back( child );
        child->stage	= this->stage;
        child->parent	= this;
        child->level( this->level() + 1 );
	}
}

void ofxFlashMovieClip :: removeFrameChildren ()
{
	ofxFlashDisplayObjectContainer :: removeAllChildren();
}

///////////////////////////////////////////////
//	MOVIE CLIP METHODS.
///////////////////////////////////////////////

void ofxFlashMovieClip :: gotoAndPlay ( int frameNum )
{
	int index = frameNum - 1;
	
	if( frameIndex != index )
	{
		frameIndex	= frameNum - 1;
		frameIndex	= ofClamp( frameIndex, 0, totalFrames() - 1 );
		frame		= frames[ frameIndex ];
	}
	
	play();
}

void ofxFlashMovieClip :: gotoAndStop ( int frameNum )
{
	int index = frameNum - 1;
	
	if( frameIndex != index )
	{
		frameIndex	= index;
		frameIndex	= ofClamp( frameIndex, 0, totalFrames() - 1 );
		frame		= frames[ frameIndex ];
	}
	
	stop();
}

void ofxFlashMovieClip :: nextFrame ()
{
	if( ++frameIndex > totalFrames() - 1 )
	{
		frameIndex = 0;
	}
	
	frame = frames[ frameIndex ];
}

void ofxFlashMovieClip :: prevFrame ()
{
	if( --frameIndex < 0 )
	{
		frameIndex = totalFrames() - 1;
	}
	
	frame = frames[ frameIndex ];
}

void ofxFlashMovieClip :: play ()
{
	bPlay = true;
}

void ofxFlashMovieClip :: stop ()
{
	bPlay = false;
}

///////////////////////////////////////////////
//	GETTERS.
///////////////////////////////////////////////

int ofxFlashMovieClip :: totalFrames ()
{
	return frames.size();
}

int ofxFlashMovieClip :: currentFrame ()
{
	return frameIndex + 1;
}