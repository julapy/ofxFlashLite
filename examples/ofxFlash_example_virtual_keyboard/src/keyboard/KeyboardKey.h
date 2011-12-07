//
//  KeyboardKey.h
//  emptyExample
//
//  Created by lukasz karluk on 30/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxFlashMovieClip.h"

#define KEY_TYPE_CHAR   0
#define KEY_CANCEL      1
#define KEY_DELETE      2
#define KEY_ENTER       3
#define KEY_ARROW       4

class KeyboardKey : public ofBaseApp
{
public:
    
     KeyboardKey();
    ~KeyboardKey();
    
    virtual void setup  ( ofxFlashMovieClip* mc );
    virtual void update ();
    virtual void draw   ();
    
    bool isNewKeyStroke ();
    
    ofxFlashMovieClip* mc;
    
    int keyType;
    string keyStroke;
    bool bKeyDown;
    bool bKeyChanged;
    
    int keyDownTimeStart;
    int keyDownTimeTotal;
};