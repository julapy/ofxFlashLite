#include "testApp.h"

void testApp::setup()
{
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener(this);
	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofSetCircleResolution(100);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofBackground(255);
	
	stage = ofxFlashStage::getInstance();			// ofxFlash setup.
	stage->showRedrawRegions(false);				// if set to true, it will draw the bounding rectangle around the object's pixels.
	stage->setTouchMode(true);                      // touch input is handled differently from mouse input - set to true on iphone / ipad.
	
    xfl.setVerbose(true);
	xfl.loadFile("assets/DOMDocument.xml");         // load XFL flash file.
	xfl.build();
}

void testApp::update()
{
	stage->update();
}

void testApp::draw()
{
	stage->draw();
}

void testApp::exit(){

}

void testApp::touchDown( int x, int y, int id )
{
	stage->mousePressed( x, y, id );
}

void testApp::touchMoved( int x, int y, int id )
{
	ofxFlashMovieClip* flashIcon;
	flashIcon = (ofxFlashMovieClip*)( stage->root()->getChildByName( "fl_icon" ) );
	
	flashIcon->x( x );
	flashIcon->y( y );
	
	stage->mouseMoved( x, y, id );
}

void testApp::touchUp( int x, int y, int id )
{
	stage->mouseReleased( x, y, id );
}

void testApp::touchDoubleTap( int x, int y, int id )
{
	//
}

void testApp::lostFocus()
{
	//
}

void testApp::gotFocus()
{
	//
}

void testApp::gotMemoryWarning()
{
	//
}

void testApp::deviceOrientationChanged(int newOrientation)
{
	//
}

