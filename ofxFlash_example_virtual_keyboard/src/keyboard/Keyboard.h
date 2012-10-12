#pragma once

#include "ofMain.h"
#include "ofxFlash.h"
#include "KeyboardKey.h"
#include "KeyboardArrowKey.h"
#include "KeyboardTextField.h"
#include "KeyboardCursor.h"

class Keyboard : public ofxFlashMovieClip
{
public:
    
     Keyboard ();
    ~Keyboard ();
    
    void setup  ();
    void update ();
    void draw   ();

    void show               ();
    void hide               ();
    void toggleUp           ();
    void toggleUpComplete   ();
    
    void keyPressed         ( int key );
		
    vector<string> keyNames;
    vector<KeyboardKey*> keys;
    KeyboardArrowKey *arrowKey;
    
    bool bUp;
    bool bAnimating;
    bool bAnimatingComplete;
    int animStartTime;
    int animTotalTime;
    int upY;
    int downY;
    
    KeyboardTextField* textField;
    KeyboardCursor* cursor;
};
