#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground( 0 );                              // OF setup.
	ofSetFrameRate( 30 );							
	ofSetVerticalSync( true );
	
	ofxFlashStage::getInstance()->addListeners();   // ofxFlash setup.
	
	xfl.loadFile( "assets/DOMDocument.xml" );		// load XFL flash file.
	xfl.build();
    
    keyboard.setup();
}

//--------------------------------------------------------------
void testApp::update()
{
    //
}

//--------------------------------------------------------------
void testApp::draw()
{
    int x = 20;
    int y = 0;
    
    ofSetColor( ofColor :: yellow );
    ofDrawBitmapString( "This is a virtual keyboard demo made using ofxFlash,", x, y+=20 );
    ofDrawBitmapString( "generously donated by Lightwell [http://lightwell.com.au/] from the Plot Your Pitch project.", x, y+=20 );
    
    ofSetColor( ofColor :: cyan );
    ofDrawBitmapString( " - use the mouse to press the keys on the virtual keyboard.", x, y+=40 );
    ofDrawBitmapString( " - you can also use your computer keyboard to input text.", x, y+=20 );
    ofDrawBitmapString( " - press the arrow key to toggle the keyboard.", x, y+=20 );
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    keyboard.keyPressed( key );
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    //
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{
    //
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    //
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    //
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    //
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    //
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
    //
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{ 
    //
}