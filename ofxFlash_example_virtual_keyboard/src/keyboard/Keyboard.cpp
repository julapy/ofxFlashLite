#include "Keyboard.h"

Keyboard :: Keyboard ()
{
    //
}

Keyboard :: ~Keyboard ()
{
    //
}

//--------------------------------------------------------------
void Keyboard::setup()
{
    ofxFlashLibrary::getInstance()->createMovieClipWithLinkageClassName( "keyboard", this );
    this->y( ofGetHeight() - 408 );
    
    ofxFlashStage::getInstance()->root()->addChild( this );
    
    int t = numChildren();
    for( int i=0; i<t; i++ )
    {
        ofxFlashDisplayObject* dispObj;
        dispObj = getChildAt( i );
        if( !dispObj )
            continue;
        if( dispObj->typeID != OFX_FLASH_TYPE_MOVIECLIP )
            continue;
        
        ofxFlashMovieClip* keyMc;
        keyMc = (ofxFlashMovieClip*)dispObj;
        
        if( keyMc->name() == "keyboard_bar" )
            continue;
        
        KeyboardKey *key;
        
        if( keyMc->name() == "key_arrow" )
        {
            key = arrowKey = new KeyboardArrowKey();
        }
        else
        {
            key = new KeyboardKey();
        }
        
        key->setup( keyMc );
        
        keys.push_back( key );
    }
    
    bUp = true;
    bAnimating = false;
    bAnimatingComplete = false;
    animStartTime = 0;
    animTotalTime = 0;
    
    upY     = this->y();
    downY   = upY + 345;
    
    textField = new KeyboardTextField();
    addChild( textField );
    
    cursor = new KeyboardCursor();
    cursor->x( 35 );
    cursor->y( 100 );
    addChild( cursor );
}

//--------------------------------------------------------------
void Keyboard::update()
{
    for( int i=0; i<keys.size(); i++ )
    {
        KeyboardKey *key = keys[ i ];
        
        key->update();
        if( key->isNewKeyStroke() )
        {
            if( key->keyType == KEY_TYPE_CHAR )
            {
                textField->addKeyStroke( key->keyStroke );
            }
            else if( key->keyType == KEY_DELETE )
            {
                textField->deleteKeyStroke();
            }
            else if( key->keyType == KEY_ENTER || key->keyType == KEY_ARROW )
            {
                arrowKey->toggleUp();
                toggleUp();
            }
        }
    }
    
    if( bAnimating )
    {
        int timeNow = ofGetElapsedTimeMillis();
        bool b = !( timeNow > animStartTime + animTotalTime );
        bAnimatingComplete = bAnimating != b;
        bAnimating = b;
        
        float p = ofNormalize( timeNow, animStartTime, animStartTime + animTotalTime );
        float t = 0;
        if( bUp )
            t = p;
        else
            t = 1 - p;
        
        float y = downY - ( downY - upY ) * t;
        
        this->y( y );
        
        if( bAnimatingComplete )
            toggleUpComplete();
    }
    
    //--- width of text.
    
    cursor->setPosition( textField->getTextFieldWidth() );
}

//-------------------------------------------------------------- show/hide.
void Keyboard :: show ()
{
    if( bUp )
        return;
    
    bUp = true;
    
    bAnimating = true;
    animStartTime = ofGetElapsedTimeMillis();
    animTotalTime = 0.3 * 1000;
}

void Keyboard :: hide ()
{
    if( !bUp )
        return;
    
    bUp = false;
    
    bAnimating = true;
    animStartTime = ofGetElapsedTimeMillis();
    animTotalTime = 0.3 * 1000;
}

void Keyboard :: toggleUp ()
{
    if( bUp )
        hide();
    else
        show();
}

void Keyboard :: toggleUpComplete ()
{
    if( !bUp )
    {
        textField->clear();
    }
}

//--------------------------------------------------------------
void Keyboard::draw()
{
    for( int i=0; i<keys.size(); i++ )
        keys[ i ]->draw();
}

//--------------------------------------------------------------
void Keyboard::keyPressed(int key)
{
    if( !bUp )
        return;
    
    if( key == OF_KEY_BACKSPACE )
    {
        textField->deleteKeyStroke();
        return;
    }
    
    if( key == OF_KEY_RETURN )
    {
        arrowKey->toggleUp();
        toggleUp();

        return;
    }
    
    string str = "";
    str += (char)key;
    textField->addKeyStroke( str );
}
