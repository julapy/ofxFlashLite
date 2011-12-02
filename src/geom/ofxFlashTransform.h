//
//  ofxFlashTransform.h
//  emptyExample
//
//  Created by lukasz karluk on 2/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"
#include "ofxFlashColorTransform.h"
#include "ofxFlashMatrix.h"
#include "ofxFlashRectangle.h"

class ofxFlashStage;
class ofxFlashDisplayObject;

class ofxFlashTransform : public ofxFlashObject
{
public:

     ofxFlashTransform ();
    ~ofxFlashTransform ();
    
    /**
     *  friends! http://www.cplusplus.com/doc/tutorial/inheritance/
     **/
    friend class ofxFlashStage;
    friend class ofxDisplayObject;
    
    /**
     *  Returns a Matrix3D object, which can transform the space of a specified display object in relation to the current display object's space.
     *  Not working due to cycling dependencies I need to work out.
     **/
//    ofxFlashMatrix getRelativeMatrix3D( ofxFlashDisplayObject relativeTo ) { return ofxFlashMatrix(); }
    
    ofxFlashColorTransform colorTransform;              // A ColorTransform object containing values that universally adjust the colors in the display object.
    ofxFlashColorTransform concatenatedColorTransform;  // [read-only] A ColorTransform object representing the combined color transformations applied to the display object and all of its parent objects, back to the root level.
    ofxFlashMatrix concatenatedMatrix;                  // [read-only] A Matrix object representing the combined transformation matrixes of the display object and all of its parent objects, back to the root level.
    ofxFlashMatrix matrix;                              // A Matrix object containing values that alter the scaling, rotation, and translation of the display object.
    ofxFlashMatrix matrix3D;                            // Provides access to the Matrix3D object of a three-dimensional display object.
    ofxFlashRectangle pixelBounds;                      // [read-only] A Rectangle object that defines the bounding rectangle of the display object on the stage.
    
protected:
    
    void update ();
    
private:
    
    bool bDirtyColorTransform;
    bool bDirtyMatrix;
    bool bDirtyMatrix3D;
    
    ofxFlashColorTransform  _colorTransform;
    ofxFlashColorTransform  _concatenatedColorTransform;
    ofxFlashMatrix          _concatenatedMatrix;
    ofxFlashMatrix          _concatenatedMatrixInv;
    ofxFlashMatrix          _matrix;
    ofxFlashMatrix          _matrix3D;
    ofxFlashRectangle       _pixelBounds;
    ofxFlashRectangle       _rect;
    ofPoint                 _rectTransformed[ 4 ];
};