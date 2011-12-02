//
//  ofxFlashColorTransform.h
//  PYPEarth
//
//  Created by lukasz karluk on 2/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxFlashObject.h"

class ofxFlashColorTransform : public ofxFlashObject
{
public:

    ofxFlashColorTransform
    ( 
        float redMultiplier     = 1,
        float greenMultiplier   = 1,
        float blueMultiplier    = 1,
        float alphaMultiplier   = 1,
        float redOffset         = 0,
        float greenOffset       = 0,
        float blueOffset        = 0,
        float alphaOffset       = 0
    );
    
    ~ofxFlashColorTransform ();
    
    void set        ( const ofxFlashColorTransform &second );
    void concat     ( const ofxFlashColorTransform &second );
    bool isEqual    ( const ofxFlashColorTransform &second );
    string toString ();
    
    float alphaMultiplier;  // A decimal value that is multiplied with the alpha transparency channel value.
    float alphaOffset;      // A number from -255 to 255 that is added to the alpha transparency channel value after it has been multiplied by the alphaMultiplier value.
    float blueMultiplier;   // A decimal value that is multiplied with the blue channel value.
    float blueOffset;       // A number from -255 to 255 that is added to the blue channel value after it has been multiplied by the blueMultiplier value.
    unsigned int color;     // The RGB color value for a ColorTransform object.
    float greenMultiplier;  // A decimal value that is multiplied with the green channel value.
    float greenOffset;      // A number from -255 to 255 that is added to the green channel value after it has been multiplied by the greenMultiplier value.
    float redMultiplier;    // A decimal value that is multiplied with the red channel value.
    float redOffset;        // A number from -255 to 255 that is added to the red channel value after it has been multiplied by the redMultiplier value.
};