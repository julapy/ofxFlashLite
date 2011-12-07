//
//  KeyboardTextField.h
//  emptyExample
//
//  Created by lukasz karluk on 30/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxFlash.h"

class KeyboardTextField : public ofxFlashSprite
{
public:
    
     KeyboardTextField();
    ~KeyboardTextField();
    
    void setup	();
    void update	();
    void draw	();
    
    bool addKeyStroke       ( string keyStroke );
    bool deleteKeyStroke    ();

    float getTextFieldWidth ();
    string getText          () { return text; }
    void clear              ();
    
    ofTrueTypeFont font;
    string text;
    int charLimit;
};