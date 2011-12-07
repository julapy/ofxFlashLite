//
//  KeyboardKey.cpp
//  emptyExample
//
//  Created by lukasz karluk on 30/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "KeyboardKey.h"

KeyboardKey :: KeyboardKey()
{
    keyType = KEY_TYPE_CHAR;
    keyStroke = "";
    bKeyDown = false;
    
    keyDownTimeStart = 0;
    keyDownTimeTotal = 0;
    
    mc = NULL;
}

KeyboardKey :: ~KeyboardKey()
{
    //
}

void KeyboardKey :: setup ( ofxFlashMovieClip* mc )
{
    this->mc = mc;
    mc->mouseEnabled( true );
    mc->gotoAndStop( 1 );

    keyStroke = ofSplitString( mc->name(), "_" ).back();
    if( keyStroke == "hash" )       keyStroke = "#";
    if( keyStroke == "at" )         keyStroke = "@";
    if( keyStroke == "dot" )        keyStroke = ".";
    if( keyStroke == "comma" )      keyStroke = ",";
    if( keyStroke == "dash" )       keyStroke = "-";
    if( keyStroke == "underscore" ) keyStroke = "_";
    if( keyStroke == "space" )      keyStroke = " ";
    
    if( keyStroke == "cancel" )     keyType = KEY_CANCEL;
    if( keyStroke == "delete" )     keyType = KEY_DELETE;
    if( keyStroke == "enter" )      keyType = KEY_ENTER;
    if( keyStroke == "arrow" )      keyType = KEY_ARROW;
}

void KeyboardKey :: update ()
{
    bKeyChanged = bKeyDown != mc->mouseDown();
    bKeyDown    = mc->mouseDown();
    
    int timeNow = ofGetElapsedTimeMillis();
    
    if( bKeyDown )
    {
        if( bKeyChanged )
        {
            keyDownTimeStart = timeNow;
            keyDownTimeTotal = 1000 * 0.5;
        }
        else
        {
            if( keyDownTimeStart + keyDownTimeTotal < timeNow )
            {
                keyDownTimeStart = timeNow;
                keyDownTimeTotal = 1000 * 0.1;
                bKeyChanged = true;
            }
        }
    }
    
    if( bKeyChanged )
    {
        if( bKeyDown )
            mc->gotoAndStop( 2 );
        else
            mc->gotoAndStop( 1 );
    }
}

bool KeyboardKey :: isNewKeyStroke ()
{
    return bKeyDown && bKeyChanged;
}

void KeyboardKey :: draw ()
{
    //
}
