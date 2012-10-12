//
//  KeyboardArrowKey.cpp
//  emptyExample
//
//  Created by lukasz karluk on 27/10/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "KeyboardArrowKey.h"

KeyboardArrowKey :: KeyboardArrowKey ()
{
    bUp = false;
    bAnimating = false;
    animStartTime = 0;
    animTotalTime = 0;
}

KeyboardArrowKey :: ~KeyboardArrowKey ()
{
    //
}

void KeyboardArrowKey :: setup ( ofxFlashMovieClip* mc )
{
    KeyboardKey :: setup( mc );
    arrowMc = (ofxFlashMovieClip*)mc->getChildByName( "mc" );
}

void KeyboardArrowKey :: update ()
{
    KeyboardKey :: update();
    
    if( bAnimating )
    {
        int timeNow = ofGetElapsedTimeMillis();
        bAnimating = !( timeNow > animStartTime + animTotalTime );
        
        float p = ofNormalize( timeNow, animStartTime, animStartTime + animTotalTime );
        float t = 0;
        if( bUp )
            t = p;
        else
            t = 1 - p;
        
        arrowMc->rotation( t * 180 );
    }
}

void KeyboardArrowKey :: toggleUp ()
{
    bUp = !bUp;
    
    bAnimating = true;
    animStartTime = ofGetElapsedTimeMillis();
    animTotalTime = 0.3 * 1000;
}