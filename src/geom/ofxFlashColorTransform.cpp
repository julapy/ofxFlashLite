//
//  ofxFlashColorTransform.cpp
//  PYPEarth
//
//  Created by lukasz karluk on 2/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxFlashColorTransform.h"

ofxFlashColorTransform :: ofxFlashColorTransform
( 
    float redMultiplier,
    float greenMultiplier,
    float blueMultiplier,
    float alphaMultiplier,
    float redOffset,
    float greenOffset,
    float blueOffset,
    float alphaOffset
)
{
    this->redMultiplier     = redMultiplier;
    this->greenMultiplier   = greenMultiplier;
    this->blueMultiplier    = blueMultiplier;
    this->alphaMultiplier   = alphaMultiplier;
    this->redOffset         = redOffset;
    this->greenOffset       = greenOffset;
    this->blueOffset        = blueOffset;
    this->alphaOffset       = alphaOffset;
    
    color = 0xFFFFFF;
}

ofxFlashColorTransform :: ~ofxFlashColorTransform ()
{
    //
}

/**
 *  Concatenates the ColorTranform object specified by the second parameter with the current ColorTransform object 
 *  and sets the current object as the result, which is an additive combination of the two color transformations.
 **/
void ofxFlashColorTransform :: concat ( const ofxFlashColorTransform &second )
{
    // not sure how flash concats these transforms. will have to look into it.
}

void ofxFlashColorTransform :: set ( const ofxFlashColorTransform &second )
{
    alphaMultiplier = second.alphaMultiplier;
    alphaOffset     = second.alphaOffset;
    blueMultiplier  = second.blueMultiplier;
    blueOffset      = second.blueOffset;
    color           = second.color;
    greenMultiplier = second.greenMultiplier;
    greenOffset     = second.greenOffset;
    redMultiplier   = second.redMultiplier;
    redOffset       = second.redOffset;
}

bool ofxFlashColorTransform :: isEqual ( const ofxFlashColorTransform &second )
{
    if( alphaMultiplier != second.alphaMultiplier ) return false;
    if( alphaOffset     != second.alphaOffset     ) return false;
    if( blueMultiplier  != second.blueMultiplier  ) return false;
    if( blueOffset      != second.blueOffset      ) return false;
    if( color           != second.color           ) return false;
    if( greenMultiplier != second.greenMultiplier ) return false;
    if( greenOffset     != second.greenOffset     ) return false;
    if( redMultiplier   != second.redMultiplier   ) return false;
    if( redOffset       != second.redOffset       ) return false;
    
    return true;
}

/**
 *  Formats and returns a string that describes all of the properties of the ColorTransform object.
 **/
string ofxFlashColorTransform :: toString ()
{
    string str = "";
    str += "(";
    str += "redMultiplier="     + ofToString( redMultiplier )   + ", ";
    str += "greenMultiplier="   + ofToString( greenMultiplier ) + ", ";
    str += "blueMultiplier="    + ofToString( blueMultiplier )  + ", ";
    str += "alphaMultiplier="   + ofToString( alphaMultiplier ) + ", ";
    str += "redOffset="         + ofToString( redOffset )       + ", ";
    str += "greenOffset="       + ofToString( greenOffset )     + ", ";
    str += "blueOffset="        + ofToString( blueOffset )      + ", ";
    str += "alphaOffset="       + ofToString( blueOffset )      + ")";
    
    return str;
}
