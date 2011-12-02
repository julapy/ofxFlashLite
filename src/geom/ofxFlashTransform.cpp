//
//  ofxFlashTransform.cpp
//  emptyExample
//
//  Created by lukasz karluk on 2/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxFlashTransform.h"

ofxFlashTransform :: ofxFlashTransform ()
{
    //
}

ofxFlashTransform :: ~ofxFlashTransform ()
{
    //
}

void ofxFlashTransform :: update ()
{
    bDirtyColorTransform = !_colorTransform.isEqual( colorTransform );
    bDirtyMatrix         = !_matrix.isEqual( matrix );
    bDirtyMatrix3D       = !_matrix3D.isEqual( matrix3D );
    
    if( bDirtyColorTransform )
        _colorTransform.set( colorTransform );
    
    if( bDirtyMatrix )
        _matrix.set( matrix );
    
    if( bDirtyMatrix3D )
        _matrix3D.set( matrix3D );
}
