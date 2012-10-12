//
//  KeyboardCursor.h
//  emptyExample
//
//  Created by lukasz karluk on 3/11/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxFlashSprite.h"

class KeyboardCursor : public ofxFlashSprite
{
public:
    
    KeyboardCursor () 
    {
        cursorStartTime = 0;
        cursorBlinkTime = 1000 * 0.5;
        bCursorBlink    = false;
    }
    
    ~KeyboardCursor () 
    {
        //
    }
    
    void setPosition ( int posX )
    {
        cursorX = posX + 13;
    }
    
    void update ()
    {
        int timeNow = ofGetElapsedTimeMillis();
        if( timeNow >= cursorStartTime + cursorBlinkTime )
        {
            cursorStartTime = timeNow;
            bCursorBlink    = !bCursorBlink;
        }
    }
    
    void draw ()
    {
        if( bCursorBlink )
        {
            ofFill();
            ofSetColor( 255 );
            ofRect( cursorX, 0, 1, 30 );
        }        
    }
    
    int cursorX;
    int cursorStartTime;
    int cursorBlinkTime;
    bool bCursorBlink;
};