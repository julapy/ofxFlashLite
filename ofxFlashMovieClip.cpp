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
	typeID = OFX_FLASH_MOVIE_CLIP_TYPE;
	
	frame = new ofxFlashDisplayObjectContainer();		// create a single frame.
	frames.push_back( frame );							// add first frame to frames.
	frameIndex = 0;
	
	play();
}

ofxFlashMovieClip :: ~ofxFlashMovieClip()
{
	//
}

///////////////////////////////////////////////
//	SETUP.
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

ofxFlashDisplayObject* ofxFlashMovieClip :: addChildToFrame( ofxFlashDisplayObject* child, int frameNum )
{
	int index = ofClamp( frameNum - 1, 0, totalFrames() - 1 );
	
	ofxFlashDisplayObjectContainer* frameContainer;
	frameContainer = frames[ index ];
	frameContainer->addChild( child );
	
	if( index == frameIndex )		// add to current frame if frameIndex matches.
	{
		addChild( child );
	}
	
	return child;
}

///////////////////////////////////////////////
//	CORE.
///////////////////////////////////////////////

void ofxFlashMovieClip :: setup ()
{
	//
}

void ofxFlashMovieClip :: update ()
{
	removeFrameChildren();			// remove + add is done on every frame. not a good idea, but will go with it for now.
	
	if( bPlay )
	{
		nextFrame();
	}
	
	addFrameChildren();
}

void ofxFlashMovieClip :: draw ()
{
	//
}

///////////////////////////////////////////////
//	FRAME CHILDREN.
///////////////////////////////////////////////

void ofxFlashMovieClip :: addFrameChildren ()
{
	for( int i=0; i<frame->children.size(); i++ )
	{
		addChild( frame->children[ i ] );
	}
}

void ofxFlashMovieClip :: removeFrameChildren ()
{
	for( int i=0; i<frame->children.size(); i++ )
	{
		removeChild( frame->children[ i ] );
	}
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