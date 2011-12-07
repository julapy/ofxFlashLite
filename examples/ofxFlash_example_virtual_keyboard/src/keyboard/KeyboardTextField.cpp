//
//  KeyboardTextField.cpp
//  emptyExample
//
//  Created by lukasz karluk on 30/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "KeyboardTextField.h"

KeyboardTextField :: KeyboardTextField()
{
    text = "";
    
    charLimit = 40;
    
    x( 45 );
    y( 124 );

    font.loadFont( "fonts/times.ttf", 20 );
}

KeyboardTextField :: ~KeyboardTextField()
{
    //
}

void KeyboardTextField :: setup	()
{
    //
}

void KeyboardTextField :: update ()
{
    //
}

void KeyboardTextField :: draw ()
{
    ofSetColor( 255 );
    font.drawString( text, 0, 0 );
}

bool KeyboardTextField :: addKeyStroke ( string keyStroke )
{
    if( text.size() >= charLimit )
        return false;
    
    text += ofToUpper( keyStroke );
    return true;
}

bool KeyboardTextField :: deleteKeyStroke ()
{
    if( text.size() == 0 )
        return false;
    
    text.erase( text.end() - 1, text.end() );
    return true;
}

float KeyboardTextField :: getTextFieldWidth ()
{
    return font.getStringBoundingBox( text, 0, 0 ).width;
}

void KeyboardTextField :: clear ()
{
    text.clear();
}