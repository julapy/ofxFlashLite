#include "testApp.h"

///////////////////////////////////////////
//	INIT.
///////////////////////////////////////////

void testApp::setup()
{
	ofSetFrameRate( 30 );							// OF setup.
	ofSetVerticalSync( true );
	ofSetCircleResolution( 100 );
	ofEnableSmoothing();
	ofBackground( 255, 255, 255 );
	
	
	ofxFlashStage* stage;
	stage = ofxFlashStage :: getInstance();			// ofxFlash setup.
	stage->addListeners();
	stage->showRedrawRegions( false );
	
	
	for( int i=0; i<20; i++ )						// adding Box sprites to stage.
	{
		Box* box;
		box	= new Box();
		
		box->name( "box_" + ofToString( i, 0 ) );
		box->mouseEnabled( true );
		
		box->x( ofRandom( 0, ofGetWidth() ) );
		box->y( ofRandom( 0, ofGetHeight() ) );
		box->rotation( ofRandom( 0, 360 ) );
		
		stage->addChild( box );
	}
}

///////////////////////////////////////////
//	UPDATE.
///////////////////////////////////////////

void testApp::update()
{
	//
}

///////////////////////////////////////////
//	DRAW.
///////////////////////////////////////////

void testApp::draw()
{
	//
}

///////////////////////////////////////////
//	HANDLERS.
///////////////////////////////////////////

void testApp::keyPressed(int key)
{

}

void testApp::keyReleased(int key)
{

}

void testApp::mouseMoved(int x, int y )
{
	
}

void testApp::mouseDragged(int x, int y, int button)
{

}

void testApp::mousePressed(int x, int y, int button)
{

}

void testApp::mouseReleased(int x, int y, int button)
{

}

void testApp::windowResized(int w, int h)
{

}

