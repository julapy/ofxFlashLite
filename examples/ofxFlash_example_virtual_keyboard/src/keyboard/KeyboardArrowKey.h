//
//  KeyboardArrowKey.h
//  emptyExample
//
//  Created by lukasz karluk on 27/10/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "KeyboardKey.h"

class KeyboardArrowKey : public KeyboardKey
{
public:
     KeyboardArrowKey ();
    ~KeyboardArrowKey ();
    
    void setup      ( ofxFlashMovieClip* mc );
    void update     ();
    void toggleUp   ();
    
    bool bUp;
    bool bAnimating;
    int animStartTime;
    int animTotalTime;
    
    ofxFlashMovieClip *arrowMc;
};